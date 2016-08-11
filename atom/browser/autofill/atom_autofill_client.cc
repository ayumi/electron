// Copyright (c) 2016 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/autofill/atom_autofill_client.h"

#include <utility>

#include "atom/browser/autofill/personal_data_manager_factory.h"
#include "atom/browser/api/atom_api_web_contents.h"
#include "atom/common/native_mate_converters/string16_converter.h"
#include "base/bind.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "base/memory/ptr_util.h"
#include "build/build_config.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "components/autofill/content/browser/content_autofill_driver.h"
#include "components/autofill/content/browser/content_autofill_driver_factory.h"
#include "components/autofill/core/browser/webdata/autofill_webdata_service.h"
#include "components/autofill/core/common/autofill_pref_names.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/common/origin_util.h"

DEFINE_WEB_CONTENTS_USER_DATA_KEY(autofill::AtomAutofillClient);

// stubs TODO - move to separate files
#include "net/http/http_request_headers.h"
namespace variations {
void AppendVariationHeaders(const GURL& url,
                            bool incognito,
                            bool uma_enabled,
                            net::HttpRequestHeaders* headers) {
}
}

namespace rappor {
void SampleDomainAndRegistryFromGURL(RapporService* rappor_service,
                                     const std::string& metric,
                                     const GURL& gurl) {}
}  // namespace rappor
// end stubs

namespace autofill {

AtomAutofillClient::AtomAutofillClient(content::WebContents* web_contents)
    : content::WebContentsObserver(web_contents) {
  DCHECK(web_contents);
}

AtomAutofillClient::~AtomAutofillClient() {
}

void AtomAutofillClient::Initialize(atom::api::WebContents* api_web_contents) {
  api_web_contents_ = api_web_contents;
}

PersonalDataManager* AtomAutofillClient::GetPersonalDataManager() {
  content::BrowserContext* context = web_contents()->GetBrowserContext();
  return PersonalDataManagerFactory::GetForBrowserContext(
        chrome::GetBrowserContextRedirectedInIncognito(context));
}

scoped_refptr<AutofillWebDataService> AtomAutofillClient::GetDatabase() {
  scoped_refptr<AutofillWebDataService> service;
  // Profile* profile =
  //     Profile::FromBrowserContext(web_contents()->GetBrowserContext());
  // return WebDataServiceFactory::GetAutofillWebDataForProfile(
  //     profile, ServiceAccessType::EXPLICIT_ACCESS);
  return service;
}

PrefService* AtomAutofillClient::GetPrefs() {
  return user_prefs::UserPrefs::Get(web_contents()->GetBrowserContext());
}

sync_driver::SyncService* AtomAutofillClient::GetSyncService() {
  return nullptr;
}

IdentityProvider* AtomAutofillClient::GetIdentityProvider() {
  return nullptr;
}

rappor::RapporService* AtomAutofillClient::GetRapporService() {
  return nullptr;
}

void AtomAutofillClient::ShowAutofillSettings() {
  LOG(ERROR) << __PRETTY_FUNCTION__;
  api_web_contents_->Emit("show-autofill-settings");
}

void AtomAutofillClient::ShowUnmaskPrompt(
    const CreditCard& card,
    UnmaskCardReason reason,
    base::WeakPtr<CardUnmaskDelegate> delegate) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void AtomAutofillClient::OnUnmaskVerificationResult(
    PaymentsRpcResult result) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void AtomAutofillClient::ConfirmSaveCreditCardLocally(
    const CreditCard& card,
    const base::Closure& callback) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void AtomAutofillClient::ConfirmSaveCreditCardToCloud(
    const CreditCard& card,
    std::unique_ptr<base::DictionaryValue> legal_message,
    const base::Closure& callback) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void AtomAutofillClient::LoadRiskData(
    const base::Callback<void(const std::string&)>& callback) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

bool AtomAutofillClient::HasCreditCardScanFeature() {
  return false;
}

void AtomAutofillClient::ScanCreditCard(
    const CreditCardScanCallback& callback) {
}

void AtomAutofillClient::ShowAutofillPopup(
    const gfx::RectF& element_bounds,
    base::i18n::TextDirection text_direction,
    const std::vector<autofill::Suggestion>& suggestions,
    base::WeakPtr<AutofillPopupDelegate> delegate) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
}

void AtomAutofillClient::UpdateAutofillPopupDataListValues(
    const std::vector<base::string16>& values,
    const std::vector<base::string16>& labels) {
  LOG(ERROR) << __PRETTY_FUNCTION__;
  LOG(ERROR) << values.size();
  for (auto i = values.begin(); i != values.end(); ++i) {
    LOG(ERROR) << *i;
  }
  LOG(ERROR) << labels.size();
  for (auto i = labels.begin(); i != labels.end(); ++i) {
    LOG(ERROR) << *i;
  }
  api_web_contents_->Emit("update-autofill-popup-data-list-values",
                          values, labels);
}

void AtomAutofillClient::HideAutofillPopup() {
  LOG(ERROR) << __PRETTY_FUNCTION__;
  api_web_contents_->Emit("hide-autofill-popup");
}

bool AtomAutofillClient::IsAutocompleteEnabled() {
  LOG(ERROR) << __PRETTY_FUNCTION__ << GetPrefs()->GetBoolean(prefs::kAutofillEnabled);
  // For browser, Autocomplete is always enabled as part of Autofill.
  //return GetPrefs()->GetBoolean(prefs::kAutofillEnabled);
  return true;
}

// void AtomAutofillClient::MainFrameWasResized(bool width_changed) {
//   HideAutofillPopup();
// }

// void AtomAutofillClient::WebContentsDestroyed() {
//   HideAutofillPopup();
// }

// void AtomAutofillClient::OnZoomChanged(
//     const ui_zoom::ZoomController::ZoomChangedEventData& data) {
//   HideAutofillPopup();
// }

void AtomAutofillClient::PropagateAutofillPredictions(
    content::RenderFrameHost* rfh,
    const std::vector<autofill::FormStructure*>& forms) {
}

void AtomAutofillClient::DidFillOrPreviewField(
    const base::string16& autofilled_value,
    const base::string16& profile_full_name) {
}

void AtomAutofillClient::OnFirstUserGestureObserved() {
  LOG(ERROR) << __PRETTY_FUNCTION__;
  ContentAutofillDriverFactory* factory =
    ContentAutofillDriverFactory::FromWebContents(web_contents());
  DCHECK(factory);

  for (content::RenderFrameHost* frame : web_contents()->GetAllFrames()) {
    // No need to notify non-live frames.
    // And actually they have no corresponding drivers in the factory's map.
    if (!frame->IsRenderFrameLive())
      continue;
    ContentAutofillDriver* driver = factory->DriverForFrame(frame);
    DCHECK(driver);
    driver->NotifyFirstUserGestureObservedInTab();
  }
}

bool AtomAutofillClient::IsContextSecure(const GURL& form_origin) {
  return content::IsOriginSecure(form_origin);
}

}  // namespace autofill
