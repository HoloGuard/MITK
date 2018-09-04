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

#ifndef QMITKLESIONINFOWIDGET_H
#define QMITKLESIONINFOWIDGET_H

// semantic relations plugin
#include <ui_QmitkLesionInfoWidgetControls.h>

// semantic relations UI module
#include <QmitkLesionTreeModel.h>

// semantic relations module
#include <mitkSemanticRelations.h>

// mitk
#include <mitkDataStorage.h>

// qt
#include <QWidget>

/*
* @brief The QmitkLesionInfoWidget is a widget that shows and modifies the currently available lesion data of the semantic relations model.
*
*   The widget provides a dialogs to add nodes from the data storage to the semantic relations model.
*   It provides functionality to create new lesions and link them with segmentation nodes.
*
*   The QmitkLesionInfoWidget provides three QListWidgets, that show the lesion data and the referenced segmentation data, as
*   well as the connected image data, depending on the selected lesion.
*/
class QmitkLesionInfoWidget : public QWidget
{
  Q_OBJECT

public:

  static const QBrush DEFAULT_BACKGROUND_COLOR;
  static const QBrush SELECTED_BACKGROUND_COLOR;
  static const QBrush CONNECTED_BACKGROUND_COLOR;

  QmitkLesionInfoWidget::QmitkLesionInfoWidget(mitk::DataStorage* dataStorage, QWidget* parent = nullptr);
  ~QmitkLesionInfoWidget();

  void SetCaseID(const mitk::SemanticTypes::CaseID& caseID);

  const mitk::SemanticTypes::Lesion& GetSelectedLesion() const { return m_CurrentLesion; }

Q_SIGNALS:

  void LesionChanged(const mitk::SemanticTypes::Lesion&);

private Q_SLOTS:

  void OnModelUpdated();
  /*
  * @brief Generates a new, empty lesion to add to the semantic relations model for the current case ID.
  */
  void OnAddLesionButtonClicked();

  // slots for the mouse click events of the list widgets
  void OnSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
  //void OnLesionItemDoubleClicked(QListWidgetItem*);

  void OnLesionListContextMenuRequested(const QPoint&);

  // slots for the context menu actions of the lesion list widget
  void OnLinkToSegmentation(mitk::SemanticTypes::Lesion);
  void OnSetLesionName(mitk::SemanticTypes::Lesion);
  void OnSetLesionClass(mitk::SemanticTypes::Lesion);
  void OnRemoveLesion(mitk::SemanticTypes::Lesion);

private:

  void Initialize();
  void SetUpConnections();

  Ui::QmitkLesionInfoWidgetControls m_Controls;
  QmitkLesionTreeModel* m_StorageModel;

  mitk::WeakPointer<mitk::DataStorage> m_DataStorage;
  std::unique_ptr<mitk::SemanticRelations> m_SemanticRelations;
  mitk::SemanticTypes::CaseID m_CaseID;

  mitk::SemanticTypes::Lesion m_CurrentLesion;
};

#endif // QMITKLESIONINFOWIDGET_H
