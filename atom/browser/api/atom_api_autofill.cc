// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_autofill.h"

#include "atom/common/native_mate_converters/string16_converter.h"
#include "atom/common/native_mate_converters/value_converter.h"
#include "base/values.h"
#include "content/public/browser/browser_thread.h"

#include "atom/common/native_mate_converters/v8_value_converter.h"

namespace mate {

template<>
struct Converter<const base::DictionaryValue*> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const base::DictionaryValue* val) {
    std::unique_ptr<atom::V8ValueConverter>
        converter(new atom::V8ValueConverter);
    return converter->ToV8Value(val, isolate->GetCurrentContext());
  }
};

template<>
struct Converter<const base::ListValue*> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const base::ListValue* val) {
    std::unique_ptr<atom::V8ValueConverter>
        converter(new atom::V8ValueConverter);
    return converter->ToV8Value(val, isolate->GetCurrentContext());
  }
};

}  // namespace mate

namespace atom {

namespace api {

Autofill::Autofill(v8::Isolate* isolate,
                 content::BrowserContext* browser_context)
      : browser_context_(browser_context) {
  Init(isolate);
  //AddObserver(this);
}

Autofill::~Autofill() {
}

void Autofill::onShowAutofillSettings() {
  Emit("show-autofill-settings");
}

void Autofill::onHideAutofillPopup() {
  Emit("hide-autofill-popup");
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void Autofill::onUpdateAutofillPopupDataListValues(
    const std::vector<base::string16>& values,
    const std::vector<base::string16>& labels) {
 Emit("update-autofill-popup-data-list-values", values, labels);
}

void Autofill::SetAutofillEnable(bool enable) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
  LOG(ERROR) << enable;
}

bool Autofill::IsAutofillEnable() {
  return true;
}

// static
mate::Handle<Autofill> Autofill::Create(
    v8::Isolate* isolate,
    content::BrowserContext* browser_context) {
  return mate::CreateHandle(isolate, new Autofill(isolate, browser_context));
}

// static
void Autofill::BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::ObjectTemplate> prototype) {
  mate::ObjectTemplateBuilder(isolate, prototype)
  .SetMethod("setAutofillEnable", &Autofill::SetAutofillEnable)
  .SetMethod("isAutofillEnable", &Autofill::IsAutofillEnable);
}

}  // namespace api

}  // namespace atom
