// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_autofill.h"

#include "atom/browser/autofill/personal_data_manager_factory.h"
#include "atom/common/native_mate_converters/string16_converter.h"
#include "atom/common/native_mate_converters/value_converter.h"
#include "base/strings/utf_string_conversions.h"
#include "base/values.h"
#include "brave/browser/brave_content_browser_client.h"
#include "components/autofill/core/browser/autofill_profile.h"
#include "components/autofill/core/browser/personal_data_manager.h"
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
}

Autofill::~Autofill() {
}

void Autofill::SetProfile(const base::DictionaryValue& profile) {
  std::string full_name, company_name, street_address, city, state, locality,
    postal_code, sorting_code, country_code, phone, email, language_code;
  profile.GetString("full_name", &full_name);
  profile.GetString("company_name", &company_name);
  profile.GetString("street_address", &street_address);
  profile.GetString("city", &city);
  profile.GetString("state", &state);
  profile.GetString("locality", &locality);
  profile.GetString("postal_code", &postal_code);
  profile.GetString("sorting_code", &sorting_code);
  profile.GetString("country_code", &country_code);
  profile.GetString("phone", &phone);
  profile.GetString("email", &email);
  profile.GetString("language_code", &language_code);
  LOG(ERROR) << full_name;
  LOG(ERROR) << company_name;
  autofill::PersonalDataManager* personal_data =
      autofill::PersonalDataManagerFactory::GetForBrowserContext(
      browser_context_);
  //if (!personal_data || !personal_data->IsDataLoaded()) {
  if (!personal_data) {
    LOG(ERROR) << "No Data";
    return;
  }

  autofill::AutofillProfile autofill_profile;
  if (!full_name.empty()) {
    autofill_profile.SetInfo(autofill::AutofillType(autofill::NAME_FULL),
                    base::UTF8ToUTF16(full_name),
                    brave::BraveContentBrowserClient::Get()
                    ->GetApplicationLocale());
  }

  if (!company_name.empty()) {
    autofill_profile.SetRawInfo(
        autofill::COMPANY_NAME,
        base::UTF8ToUTF16(company_name));
  }

  if (!street_address.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_STREET_ADDRESS,
        base::UTF8ToUTF16(street_address));
  }

  if (!city.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_CITY,
        base::UTF8ToUTF16(city));
  }

  if (!state.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_STATE,
        base::UTF8ToUTF16(state));
  }

  if (!locality.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_DEPENDENT_LOCALITY,
        base::UTF8ToUTF16(locality));
  }

  if (!postal_code.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_ZIP,
        base::UTF8ToUTF16(postal_code));
  }

  if (!sorting_code.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_SORTING_CODE,
        base::UTF8ToUTF16(sorting_code));
  }

  if (!country_code.empty()) {
    autofill_profile.SetRawInfo(
        autofill::ADDRESS_HOME_COUNTRY,
        base::UTF8ToUTF16(country_code));
  }

  if (!phone.empty()) {
    autofill_profile.SetRawInfo(autofill::PHONE_HOME_WHOLE_NUMBER,
        base::UTF8ToUTF16(phone));
  }

  if (!email.empty()) {
    autofill_profile.SetRawInfo(autofill::EMAIL_ADDRESS, base::UTF8ToUTF16(email));
  }

  if (!language_code.empty())
    autofill_profile.set_language_code(language_code);

  LOG(ERROR) << autofill_profile;
  personal_data->AddProfile(autofill_profile);
}
void Autofill::GetProfile() {}

void Autofill::SetCreditCard() {}
void Autofill::GetCreditCard() {}


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
  .SetMethod("isAutofillEnable", &Autofill::IsAutofillEnable)
  .SetMethod("setProfile", &Autofill::SetProfile)
  .SetMethod("getProfile", &Autofill::GetProfile)
  .SetMethod("setCreditCard", &Autofill::SetCreditCard)
  .SetMethod("getCreditCard", &Autofill::GetCreditCard);
}

}  // namespace api

}  // namespace atom
