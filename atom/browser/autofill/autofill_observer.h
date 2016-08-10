// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_
#define ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_

#include "base/strings/string16.h"

namespace autofill {

class AutofillObserver {
 public:

  virtual void onShowAutofillSettings() {}
  virtual void onHideAutofillPopup() {}
  virtual void onUpdateAutofillPopupDataListValues(
    const std::vector<base::string16>& values,
    const std::vector<base::string16>& labels) {}

 protected:
  virtual ~AutofillObserver() {}
};

}  // namespace autofill

#endif  // ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_
