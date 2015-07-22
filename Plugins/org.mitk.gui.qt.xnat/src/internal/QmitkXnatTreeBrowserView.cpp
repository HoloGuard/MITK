/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "QmitkXnatTreeBrowserView.h"

// Qmitk
#include "QmitkXnatObjectEditorInput.h"
#include "QmitkXnatEditor.h"
#include "org_mitk_gui_qt_xnatinterface_Activator.h"

// Blueberry
#include <berryIWorkbenchPage.h>
#include <berryPlatform.h>

// CTK XNAT Core
#include <ctkXnatAssessor.h>
#include <ctkXnatAssessorFolder.h>
#include <ctkXnatDataModel.h>
#include <ctkXnatException.h>
#include <ctkXnatExperiment.h>
#include "ctkXnatFile.h"
#include <ctkXnatProject.h>
#include <ctkXnatReconstruction.h>
#include <ctkXnatReconstructionFolder.h>
#include <ctkXnatResource.h>
#include <ctkXnatResourceFolder.h>
#include <ctkXnatScan.h>
#include <ctkXnatScanFolder.h>
#include <ctkXnatSubject.h>

// Qt
#include <QAction>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>

// MITK
#include <mitkDataStorage.h>
#include <QmitkIOUtil.h>
#include <QmitkXnatUploadFromDataStorageDialog.h>

const std::string QmitkXnatTreeBrowserView::VIEW_ID = "org.mitk.views.xnat.treebrowser";

QmitkXnatTreeBrowserView::QmitkXnatTreeBrowserView() :
m_DataStorageServiceTracker(mitk::org_mitk_gui_qt_xnatinterface_Activator::GetContext()),
m_TreeModel(new QmitkXnatTreeModel()),
m_Tracker(0),
m_DownloadPath(berry::Platform::GetPreferencesService()->GetSystemPreferences()->Node("/XnatConnection")->Get("Download Path", ""))
{
  m_DataStorageServiceTracker.open();

  // Set DownloadPath
  if (m_DownloadPath.isEmpty())
  {
    QString xnatFolder = "XNAT_DOWNLOADS";
    QDir dir(mitk::org_mitk_gui_qt_xnatinterface_Activator::GetContext()->getDataFile("").absoluteFilePath());
    dir.mkdir(xnatFolder);
    dir.setPath(dir.path() + "/" + xnatFolder);
    m_DownloadPath = dir.path() + "/";
  }
}

QmitkXnatTreeBrowserView::~QmitkXnatTreeBrowserView()
{
  delete m_TreeModel;
  delete m_Tracker;
}

void QmitkXnatTreeBrowserView::SetFocus()
{
}

void QmitkXnatTreeBrowserView::CreateQtPartControl(QWidget *parent)
{
  // Create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi(parent);
  m_Controls.treeView->setModel(m_TreeModel);
  m_Controls.treeView->header()->hide();
  m_Controls.treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  m_Controls.treeView->setAcceptDrops(true);
  m_Controls.treeView->setDropIndicatorShown(true);
  m_Controls.labelError->setText("Please use the 'Connect' button in the Preferences.");
  m_Controls.labelError->setStyleSheet("QLabel { color: red; }");

  m_SelectionProvider = new berry::QtSelectionProvider();
  this->SetSelectionProvider();
  m_Controls.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
  m_Controls.treeView->setContextMenuPolicy(Qt::CustomContextMenu);

  m_Controls.groupBox->hide();

  m_Tracker = new mitk::XnatSessionTracker(mitk::org_mitk_gui_qt_xnatinterface_Activator::GetXnatModuleContext());

  m_ContextMenu = new QMenu(m_Controls.treeView);

  connect(m_Controls.treeView, SIGNAL(customContextMenuRequested(const QPoint&)),
    this, SLOT(OnContextMenuRequested(const QPoint&)));
  connect(m_Tracker, SIGNAL(AboutToBeClosed(ctkXnatSession*)), this, SLOT(CleanTreeModel(ctkXnatSession*)));
  connect(m_Tracker, SIGNAL(Opened(ctkXnatSession*)), this, SLOT(UpdateSession(ctkXnatSession*)));

  m_Tracker->Open();

  ctkXnatSession* session;

  try
  {
    session = mitk::org_mitk_gui_qt_xnatinterface_Activator::GetXnatModuleContext()->GetService(
      mitk::org_mitk_gui_qt_xnatinterface_Activator::GetXnatModuleContext()->GetServiceReference<ctkXnatSession>());
  }
  catch (std::invalid_argument)
  {
    session = 0;
  }

  if (session != 0)
  {
    m_Controls.labelError->setVisible(false);
  }
  else
  {
    m_Controls.labelError->setVisible(true);
  }

  connect(m_Controls.treeView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(OnActivatedNode(const QModelIndex&)));
  connect(m_Controls.treeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(OnXnatNodeSelected(const QModelIndex&)));
  connect(m_TreeModel, SIGNAL(ResourceDropped(const QList<mitk::DataNode*>&, ctkXnatObject*, const QModelIndex&)), this, SLOT(OnUploadResource(const QList<mitk::DataNode*>&, ctkXnatObject*, const QModelIndex&)));

  connect(m_Controls.btnXnatUpload, SIGNAL(clicked()), this, SLOT(OnUploadFromDataStorage()));
  connect(m_Controls.btnXnatDownload, SIGNAL(clicked()), this, SLOT(OnDownloadSelectedXnatFile()));
  connect(m_Controls.btnCreateXnatFolder, SIGNAL(clicked()), this, SLOT(OnCreateResourceFolder()));
}

void QmitkXnatTreeBrowserView::OnCreateResourceFolder()
{
  QModelIndex index = m_Controls.treeView->selectionModel()->currentIndex();

  if(!index.isValid()) return;

  ctkXnatObject* parent = index.data(Qt::UserRole).value<ctkXnatObject*>();

  this->InternalAddResourceFolder(parent);
  m_TreeModel->refresh(index);
}

void QmitkXnatTreeBrowserView::OnDownloadSelectedXnatFile()
{
  QModelIndex index = m_Controls.treeView->selectionModel()->currentIndex();

  if(!index.isValid()) return;

  ctkXnatObject* selectedXnatObject = index.data(Qt::UserRole).value<ctkXnatObject*>();

  ctkXnatFile* selectedXnatFile = dynamic_cast<ctkXnatFile*>(selectedXnatObject);

  if (selectedXnatFile != nullptr)
  {
    this->InternalFileDownload(index, true);
  }
}

void QmitkXnatTreeBrowserView::OnUploadFromDataStorage()
{
  QmitkXnatUploadFromDataStorageDialog dialog;
  dialog.SetDataStorage(this->GetDataStorage());
  int result = dialog.exec();

  if (result == QmitkXnatUploadFromDataStorageDialog::UPLOAD)
  {
    QList<mitk::DataNode*> nodes;
    nodes << dialog.GetSelectedNode().GetPointer();
    QModelIndex index = m_Controls.treeView->selectionModel()->currentIndex();

    if (!index.isValid()) return;
    ctkXnatObject* parent = m_TreeModel->xnatObject(index);
    this->OnUploadResource(nodes, parent, index);
  }
}

void QmitkXnatTreeBrowserView::OnXnatNodeSelected(const QModelIndex& index)
{
  // Enable download button
  if (!index.isValid()) return;

  ctkXnatObject* selectedXnatObject = index.data(Qt::UserRole).value<ctkXnatObject*>();

  bool enableDownload = dynamic_cast<ctkXnatFile*>(selectedXnatObject);
  m_Controls.btnXnatDownload->setEnabled(enableDownload);

  bool enableCreateFolder = dynamic_cast<ctkXnatProject*>(selectedXnatObject) != nullptr;
  enableCreateFolder |= dynamic_cast<ctkXnatSubject*>(selectedXnatObject) != nullptr;
  enableCreateFolder |= dynamic_cast<ctkXnatExperiment*>(selectedXnatObject) != nullptr;
  m_Controls.btnCreateXnatFolder->setEnabled(enableCreateFolder);

  bool enableUpload = dynamic_cast<ctkXnatResource*>(selectedXnatObject) != nullptr;
  m_Controls.btnXnatUpload->setEnabled(enableUpload);
}

void QmitkXnatTreeBrowserView::OnActivatedNode(const QModelIndex& index)
{
  if (!index.isValid()) return;

  berry::IWorkbenchPage::Pointer page = GetSite()->GetPage();
  QmitkXnatObjectEditorInput::Pointer oPtr(new QmitkXnatObjectEditorInput(index.data(Qt::UserRole).value<ctkXnatObject*>()));
  berry::IEditorInput::Pointer editorInput(oPtr);
  berry::IEditorPart::Pointer reuseEditor = page->FindEditor(editorInput);

  if (reuseEditor)
  {
    // Just set it activ
    page->Activate(reuseEditor);
  }
  else
  {
    QList<berry::IEditorReference::Pointer> editors =
      page->FindEditors(berry::IEditorInput::Pointer(0), QmitkXnatEditor::EDITOR_ID, berry::IWorkbenchPage::MATCH_ID);

    if (editors.isEmpty())
    {
      ctkXnatFile* file = dynamic_cast<ctkXnatFile*>(oPtr->GetXnatObject());
      if (file != NULL)
      {
        // If the selected node is a file, so show it in MITK
        InternalFileDownload(index, true);
      }
      else
      {
        // No XnatEditor is currently open, create a new one
        page->OpenEditor(editorInput, QmitkXnatEditor::EDITOR_ID);
      }
    }
    else
    {
      // Reuse an existing editor
      reuseEditor = editors.front()->GetEditor(true);
      page->ReuseEditor(reuseEditor.Cast<berry::IReusableEditor>(), editorInput);
      page->Activate(reuseEditor);
    }
  }
}

void QmitkXnatTreeBrowserView::SetSelectionProvider()
{
  GetSite()->SetSelectionProvider(m_SelectionProvider);
}

void QmitkXnatTreeBrowserView::UpdateSession(ctkXnatSession* session)
{
  if (session != 0 && session->isOpen())
  {
    m_Controls.labelError->setVisible(false);
    // Fill model and show in the GUI
    m_TreeModel->addDataModel(session->dataModel());
    m_Controls.treeView->reset();
    m_SelectionProvider->SetItemSelectionModel(m_Controls.treeView->selectionModel());

    connect(session, SIGNAL(progress(QUuid,double)), this, SLOT(OnProgress(QUuid,double)));
  }
}

void QmitkXnatTreeBrowserView::CleanTreeModel(ctkXnatSession* session)
{
  if (session != 0)
  {
    m_TreeModel->removeDataModel(session->dataModel());
    m_Controls.treeView->reset();
  }
}

void QmitkXnatTreeBrowserView::OnProgress(QUuid /*queryID*/, double progress)
{
  unsigned int currentProgress = progress*100;
  if (m_Controls.groupBox->isHidden())
  {
    m_Controls.groupBox->show();
    m_Controls.progressBar->setValue(0);
  }
  m_Controls.progressBar->setValue(currentProgress);
}

void QmitkXnatTreeBrowserView::InternalFileDownload(const QModelIndex& index, bool loadData)
{
  QVariant variant = m_TreeModel->data(index, Qt::UserRole);
  if (variant.isValid())
  {
    ctkXnatFile* file = dynamic_cast<ctkXnatFile*>(variant.value<ctkXnatObject*>());
    if (file != NULL)
    {
      QDir downDir(m_DownloadPath);
      QString filePath = m_DownloadPath + file->name();

      // Checking if the file exists already
      if (downDir.exists(file->name()))
      {
        MITK_INFO << "File '" << file->name().toStdString() << "' already exists!";
      }
      else
      {
        MITK_INFO << "Download started ...";

        m_Controls.groupBox->setTitle("Downloading file...");
        m_Controls.groupBox->show();
        m_Controls.progressBar->setValue(0);

        file->download(filePath);

        // Checking if the file exists now
        if (downDir.exists(file->name()))
        {
          MITK_INFO << "Download of " << file->name().toStdString() << " completed!";
          QMessageBox msgBox;
          msgBox.setText("Download of " + file->name() + " completed!");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
          m_Controls.groupBox->hide();
        }
        else
        {
          MITK_INFO << "Download of " << file->name().toStdString() << " failed!";
          QMessageBox msgBox;
          msgBox.setText("Download of " + file->name() + " failed!");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
          m_Controls.groupBox->hide();
          return;
        }
      }

      if (downDir.exists(file->name()))
      {
        if (loadData)
        {
          mitk::IDataStorageService* dsService = m_DataStorageServiceTracker.getService();
          mitk::DataStorage::Pointer dataStorage = dsService->GetDataStorage()->GetDataStorage();
          QStringList list;
          list << (m_DownloadPath + file->name());
          try
          {
            QmitkIOUtil::Load(list, *dataStorage);
          }
          catch (const mitk::Exception& e)
          {
            MITK_INFO << e;
            return;
          }
          mitk::RenderingManager::GetInstance()->InitializeViewsByBoundingObjects(
            dsService->GetDataStorage()->GetDataStorage());
        }
      }
    }
    else
    {
      MITK_INFO << "Selection was not a file!";
    }
  }
}

void QmitkXnatTreeBrowserView::OnContextMenuDownloadFile()
{
  QModelIndex index = m_Controls.treeView->currentIndex();
  InternalFileDownload(index, false);
}

void QmitkXnatTreeBrowserView::OnContextMenuDownloadAndOpenFile()
{
  QModelIndex index = m_Controls.treeView->currentIndex();
  InternalFileDownload(index, true);
}

void QmitkXnatTreeBrowserView::OnContextMenuCreateResourceFolder()
{
  const QModelIndex index = m_Controls.treeView->selectionModel()->currentIndex();
  ctkXnatObject* parentObject = m_TreeModel->xnatObject(index);

  if (parentObject != nullptr)
  {
    this->InternalAddResourceFolder(parentObject);
  }
}

ctkXnatResource* QmitkXnatTreeBrowserView::InternalAddResourceFolder(ctkXnatObject *parent)
{
  bool ok;
  QString folderName = QInputDialog::getText(m_Controls.treeView, tr("Create XNAT resource folder"),
                                       tr("Folder name:"), QLineEdit::Normal, tr("data"), &ok);
  if (ok)
  {
    if (folderName.isEmpty())
      folderName = "NO LABEL";

    return parent->addResourceFolder(folderName);
  }
  else
  {
    return nullptr;
  }
}

void QmitkXnatTreeBrowserView::InternalFileUpload(ctkXnatFile* file)
{
  m_Controls.groupBox->setTitle("Uploading file...");
  m_Controls.groupBox->show();

  try
  {
    file->save();
    MITK_INFO << "Upload of " << file->name().toStdString() << " completed!";
    QMessageBox msgBox;
    msgBox.setText("Upload of " + file->name() + " completed!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.show();
    msgBox.exec();
  }
  catch (ctkXnatException &e)
  {
    QMessageBox msgbox;
    msgbox.setText(e.what());
    msgbox.setIcon(QMessageBox::Critical);
    msgbox.exec();
    m_Controls.progressBar->setValue(0);
  }
  m_Controls.groupBox->hide();
}

void QmitkXnatTreeBrowserView::OnContextMenuUploadFile()
{
  QString filename = QFileDialog::getOpenFileName(m_Controls.treeView, tr("Open File"), QDir::homePath());
  const QModelIndex index = m_Controls.treeView->selectionModel()->currentIndex();
  ctkXnatResource* resource = dynamic_cast<ctkXnatResource*>(m_TreeModel->xnatObject(index));
  if (resource)
  {
    ctkXnatFile* file = new ctkXnatFile(resource);
    file->setLocalFilePath(filename);
    QFileInfo fileInfo (filename);
    file->setName(fileInfo.fileName());
    this->InternalFileUpload(file);
    m_TreeModel->addChildNode(index, file);
  }
}

void QmitkXnatTreeBrowserView::OnUploadResource(const QList<mitk::DataNode*>& droppedNodes, ctkXnatObject* parentObject, const QModelIndex& parentIndex)
{
  if (parentObject == nullptr)
    return;

  //1. If not dropped on a resource, create a new folder
  ctkXnatResource* resource = dynamic_cast<ctkXnatResource*>(parentObject);
  if (resource == nullptr)
  {
    resource = this->InternalAddResourceFolder(parentObject);
  }

  if (resource == nullptr)
  {
    MITK_WARN << "Could not upload file! No resource available!";
    QMessageBox msgbox;
    msgbox.setText("Could not upload file! No resource available!");
    msgbox.setIcon(QMessageBox::Critical);
    msgbox.exec();
    return;
  }

  //2. Save files locally
  //3. Upload file
  mitk::DataNode* node = NULL;
  foreach (node, droppedNodes)
  {
    mitk::BaseData* data = node->GetData();
    if (!data)
      return;


    QString fileName (QString::fromStdString(node->GetName()));

    ctkXnatFile* xnatFile = new ctkXnatFile(resource);

    if (dynamic_cast<mitk::Image*>(data))
    {
      fileName.append(".nrrd");
    }
    else if (dynamic_cast<mitk::Surface*>(data))
    {
      fileName.append(".vtk");
    }
    else if (dynamic_cast<mitk::PointSet*>(data))
    {
      fileName.append(".mps");
    }
    else
    {
      MITK_WARN << "Could not upload file! File-type not supported";
      QMessageBox msgbox;
      msgbox.setText("Could not upload file! File-type not supported");
      msgbox.setIcon(QMessageBox::Critical);
      msgbox.exec();
    }

    xnatFile->setName(fileName);

    QString xnatFolder = "XNAT_UPLOADS";
    QDir dir(mitk::org_mitk_gui_qt_xnatinterface_Activator::GetContext()->getDataFile("").absoluteFilePath());
    dir.mkdir(xnatFolder);

    fileName = dir.path().append("/" + fileName);
    mitk::IOUtil::Save (data, fileName.toStdString());

    // TODO Check if file exists
    // AbstractFileReader::SetDefaultDataNodeProperties
    // und in die andere SetDefaultDataNodeProperties
    // PropertyName klein: mtime.initial + Kommentar
    mitk::StringProperty::Pointer orignalFilePath = mitk::StringProperty::New();
    node->GetProperty(orignalFilePath, "path");

    xnatFile->setLocalFilePath(fileName);

    this->InternalFileUpload(xnatFile);
    MITK_INFO << "XNAT-OBJECT: "<<m_TreeModel->xnatObject(parentIndex)->name();

//    m_TreeModel->addChildNode(parentIndex, xnatFile);
    m_TreeModel->refresh(parentIndex);

    // The filename for uploading
//    QFileInfo fileInfo;
    //      if (surface)
    //      {
    //        // Save surface
    //        fileName.append(".stl");
    //        xnatFile->setName(fileName);
    //        dir.setPath(dir.path().append("/" + fileName));

//    QString origFile = QString::fromStdString(orignalFilePath->GetValueAsString());
//    origFile.append("/" + fileName);
    //        origFile.append(".stl");

    //        fileInfo.setFile(origFile);
    //        if (!fileInfo.exists())
    //          mitk::IOUtil::SaveSurface(surface, dir.path().toStdString());
    //      }
//    this->uploadFileToXnat(xnatFile, dir.path());

    // TODO delete file!!!
  }
}

void QmitkXnatTreeBrowserView::OnContextMenuRequested(const QPoint & pos)
{
  m_ContextMenu->clear();
  QModelIndex index = m_Controls.treeView->indexAt(pos);

  ctkXnatObject* xnatObject = m_TreeModel->xnatObject(index);

  bool downloadable = false;
  downloadable |= dynamic_cast<ctkXnatFile*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatScan*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatScanFolder*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatAssessor*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatAssessorFolder*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatResource*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatReconstruction*>(xnatObject)!=NULL;
  downloadable |= dynamic_cast<ctkXnatReconstructionFolder*>(xnatObject)!=NULL;

  bool canHaveResourceFolder = false;
  canHaveResourceFolder |= dynamic_cast<ctkXnatProject*>(xnatObject) != NULL;
  canHaveResourceFolder |=  dynamic_cast<ctkXnatSubject*>(xnatObject) != NULL;
  canHaveResourceFolder |=  dynamic_cast<ctkXnatExperiment*>(xnatObject) != NULL;

  bool uploadFilePossible = false;
  uploadFilePossible |= dynamic_cast<ctkXnatResource*>(xnatObject) != NULL;
  uploadFilePossible |=  dynamic_cast<ctkXnatScan*>(xnatObject) != NULL;
  uploadFilePossible |=  dynamic_cast<ctkXnatAssessor*>(xnatObject) != NULL;

  if (downloadable)
  {
    QAction* actDownload = new QAction("Download", m_ContextMenu);
    connect(actDownload, SIGNAL(triggered()), this, SLOT(OnContextMenuDownloadFile()));
    m_ContextMenu->addAction(actDownload);
    ctkXnatFile* file = dynamic_cast<ctkXnatFile*>(xnatObject);
    if (file)
    {
      QAction* actView = new QAction("Download and Open", m_ContextMenu);
      connect(actView, SIGNAL(triggered()), this, SLOT(OnContextMenuDownloadAndOpenFile()));
      m_ContextMenu->addAction(actView);
    }
  }

  if (canHaveResourceFolder)
  {
    QAction* actCreateResource = new QAction("Add resource folder", m_ContextMenu);
    connect(actCreateResource, SIGNAL(triggered()), this, SLOT(OnContextMenuCreateResourceFolder()));
    m_ContextMenu->addAction(actCreateResource);
  }

  if (uploadFilePossible)
  {
    QAction* actUploadFile = new QAction("Upload File", m_ContextMenu);
    connect(actUploadFile, SIGNAL(triggered()), this, SLOT(OnContextMenuUploadFile()));
    m_ContextMenu->addAction(actUploadFile);
  }
  m_ContextMenu->popup(QCursor::pos());
}
