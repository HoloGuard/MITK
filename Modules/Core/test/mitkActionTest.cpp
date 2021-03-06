/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include <mitkAction.h>
#include <mitkProperties.h>

#include <fstream>
int mitkActionTest(int /*argc*/, char * /*argv*/ [])
{
  int actionId = 10;
  // Create Action
  mitk::Action::Pointer action = mitk::Action::New(actionId);

  // check ActionID
  std::cout << "check ActionId";
  if (action->GetActionId() != actionId)
  {
    std::cout << "[FAILED]" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "[PASSED]" << std::endl;

  // check properties
  action->AddProperty("boolproperty", mitk::BoolProperty::New(true));
  action->AddProperty("intproperty", mitk::IntProperty::New(10));
  action->AddProperty("floatproperty", mitk::FloatProperty::New(10.05));

  std::cout << "try adding property BOOL and read them: ";
  bool boolproperty = dynamic_cast<mitk::BoolProperty *>(action->GetProperty("boolproperty"))->GetValue();
  if (boolproperty != true)
  {
    std::cout << "[FAILED]" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "[PASSED]" << std::endl;

  std::cout << "try adding property INT and read them: ";
  int intproperty = 0;
  intproperty = dynamic_cast<mitk::IntProperty *>(action->GetProperty("intproperty"))->GetValue();
  if (intproperty != 10)
  {
    std::cout << "[FAILED]" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "[PASSED]" << std::endl;

  std::cout << "try adding property FLOAT and read them: ";
  float floatproperty = dynamic_cast<mitk::FloatProperty *>(action->GetProperty("floatproperty"))->GetValue();
  if (floatproperty != 10.05f)
  {
    std::cout << "[FAILED]" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "[PASSED]" << std::endl;

  // delete the action
  // action->Delete();

  // well done!!! Passed!
  std::cout << "[EVERYTHING PASSED]" << std::endl;

  std::cout << "[TEST DONE]" << std::endl;
  return EXIT_SUCCESS;
}
