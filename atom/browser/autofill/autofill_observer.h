// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_
#define ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_

namespace autofill {

class AutofillObserver {
 public:

  virtual void onShowAutofillSettings() {}
  virtual void onHideAutofillPopup() {}

 protected:
  virtual ~AutofillObserver() {}
};

}  // namespace autofill

#endif  // ATOM_BROWSER_AUTOFILL_AUTOFILL_OBSERVER_H_
