//
//  UDSignUpViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 6/22/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import Toast_Swift
import GooglePlaces

class UDSignUpViewController: UIViewController {
    @IBOutlet weak var firstNameTxt: ErrorTextField!
    @IBOutlet weak var LastNameTxt: ErrorTextField!
    @IBOutlet weak var emailIdTxt: ErrorTextField!
    @IBOutlet weak var passwordTxt: ErrorTextField!
    @IBOutlet weak var confirmPassword: ErrorTextField!
    @IBOutlet weak var addressTxt: ErrorTextField!
    @IBOutlet weak var postalCodeTxt: ErrorTextField!
    @IBOutlet weak var cityTxt: ErrorTextField!
    @IBOutlet weak var sateTxt: ErrorTextField!
    @IBOutlet weak var countryTxt: ErrorTextField!
    var phoneNumber = String()
    
    // Declare variables to hold address form values.
    var street_number: String = ""
    var route: String = ""
    var neighborhood: String = ""
    var locality: String = ""
    var administrative_area_level_1: String = ""
    var country: String = ""
    var postal_code: String = ""
    var postal_code_suffix: String = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        loadInitialData()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    func loadInitialData() {
        setTextView()
        setDeviceDetails()
    }
    
    func setTextView() {
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: firstNameTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: LastNameTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: emailIdTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: passwordTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: confirmPassword)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: addressTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: postalCodeTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: cityTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: sateTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: countryTxt)
    }
    
    func setDeviceDetails() {
        let userData = UserDefaults.standard.object(forKey:"userInfo") as? Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: userData!) as! NSMutableDictionary?)!
    }
    
    // Populate the address form fields.
    func fillAddressForm() {
        addressTxt.text = street_number + " " + route
        cityTxt.text = locality
        sateTxt.text = administrative_area_level_1
        if postal_code_suffix != "" {
            postalCodeTxt.text = postal_code + "-" + postal_code_suffix
        } else {
            postalCodeTxt.text = postal_code
        }
        countryTxt.text = country
    }
    
    func validateSigUpData() {
        view.endEditing(true)
        // MARK:- First Name
        let fName = (firstNameTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(fName.count == 0) {
            self.view.makeToast("Enter your First Name", position: .top)
            return
        }
        
        if fName.count > 20 {
            self.view.makeToast("First Name should not be more than 20 letters", position: .top)
            return
        }
        
        // MARK:- Last Name
        let lName = (LastNameTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(lName.count == 0) {
            self.view.makeToast("Enter your Last Name", position: .top)
            return
        }
        
        if (lName.count > 20) {
            self.view.makeToast("Last Name should not be more than 20 letters", position: .top)
            return
        }
        
        // MARK:- EmailId
        let checkEmail = ConstantTools.sharedConstantTool.isValidEmail(email: emailIdTxt.text!)
        if !checkEmail {
            self.view.makeToast("Use vaild email only", position: .top)
            return
        }
        
        // MARK:- Password
        let password = (passwordTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(password.count == 0) {
            self.view.makeToast("Enter your Password", position: .top)
            return
        }
        
        if (password.count < 3) || (password.count > 20) {
            self.view.makeToast("password must be 3 to 20 character", position: .top)
            return
        }
        
        let confirmPassword = (self.confirmPassword.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if password != confirmPassword {
            self.view.makeToast("Password does not match. Please check your password", position: .top)
            return
        }
        
        // MARK:- Address
        let address = (addressTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(address.count == 0) {
            self.view.makeToast("Enter your Address", position: .top)
            return
        }
        
        // MARK:- postalCode
        let postalCode = (postalCodeTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(postalCode.count == 0) {
            self.view.makeToast("Enter your Postal Code", position: .top)
            return
        }
        
        // MARK:- city
        let city = (cityTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(city.count == 0) {
            self.view.makeToast("Enter your City", position: .top)
            return
        }
        
        // MARK:- State
        let state = (sateTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(state.count == 0) {
            self.view.makeToast("Enter your State", position: .top)
            return
        }
        
        // MARK:- Country
        let country = (countryTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(country.count == 0) {
            self.view.makeToast("Enter your Country", position: .top)
            return
        }
        print(country)
        
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        SignUpModel.signUp(fName: fName, lName: lName, phoneNumber: phoneNumber, password: confirmPassword, emailId: emailIdTxt.text!, address: address, city: city, state: state, zip: postalCode, userDetails: userInfoDictionary, devicePlatform: userInfoDictionary.object(forKey: "systemname") as? String ?? "iOS", deviceToken: userInfoDictionary.object(forKey: "devicetoken") as? String ?? "", deviceUuid: userInfoDictionary.object(forKey: "deviceid") as? String ?? "", deviceVersion: userInfoDictionary.object(forKey: "systemversion") as! String, deviceName: userInfoDictionary.object(forKey: "name") as? String ?? "", deviceModel: userInfoDictionary.object(forKey: "model") as? String ?? "", appVersion: userInfoDictionary.object(forKey: "appVersion") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    UserDefaults.standard.set(true, forKey: "login")
                    let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                    let viewController = storyboard.instantiateViewController(withIdentifier: "UDWelcomeViewController") as! UDWelcomeViewController
                    self.navigationController?.pushViewController(viewController, animated: true)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToDismiss(_ sender: Any) {
        self.navigationController!.popViewController(animated: true)
    }
    
    @IBAction func tapToSignUP(_ sender: Any) {
        validateSigUpData()
    }
    
    @IBAction func tapToSearchAddress(_ sender: Any) {
        let autocompleteController = GMSAutocompleteViewController()
        autocompleteController.delegate = self
        // Set a filter to return only addresses.
        let addressFilter = GMSAutocompleteFilter()
        addressFilter.type = .address
        autocompleteController.autocompleteFilter = addressFilter
        present(autocompleteController, animated: true, completion: nil)
    }
}

// MARK:- TextFieldDelegates
extension UDSignUpViewController:UITextFieldDelegate {
    internal func textFieldShouldBeginEditing(_ textField: UITextField) -> Bool {
        return true
    }
    
    internal func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if let nextField = textField.superview?.viewWithTag(textField.tag + 1) as? UITextField {
            nextField.becomeFirstResponder()
        } else {
            textField.resignFirstResponder()
        }
        return false
    }
}

// MARK:- GMSAutocompleteViewControllerDelegate
extension UDSignUpViewController: GMSAutocompleteViewControllerDelegate {
    internal func viewController(_ viewController: GMSAutocompleteViewController, didAutocompleteWith place: GMSPlace) {
        // Get the address components.
        if let addressLines = place.addressComponents {
            // Populate all of the address fields we can find.
            for field in addressLines {
                switch field.type {
                case kGMSPlaceTypeStreetNumber:
                    street_number = field.name
                case kGMSPlaceTypeRoute:
                    route = field.name
                case kGMSPlaceTypeNeighborhood:
                    neighborhood = field.name
                case kGMSPlaceTypeLocality:
                    locality = field.name
                case kGMSPlaceTypeAdministrativeAreaLevel1:
                    administrative_area_level_1 = field.name
                case kGMSPlaceTypeCountry:
                    country = field.name
                case kGMSPlaceTypePostalCode:
                    postal_code = field.name
                case kGMSPlaceTypePostalCodeSuffix:
                    postal_code_suffix = field.name
                // Print the items we aren't using.
                default:
                    print("Type: \(field.type), Name: \(field.name)")
                }
            }
        }
        // Call custom function to populate the address form.
        fillAddressForm()
        
        // Close the autocomplete widget.
        self.dismiss(animated: true, completion: nil)
    }
    
    internal func viewController(_ viewController: GMSAutocompleteViewController, didFailAutocompleteWithError error: Error) {
        // TODO: handle the error.
        //        print("Error: \(error.description)")
        self.dismiss(animated: true, completion: nil)
    }
    
    // User canceled the operation.
    internal func wasCancelled(_ viewController: GMSAutocompleteViewController) {
        print("Autocomplete was cancelled.")
        self.dismiss(animated: true, completion: nil)
    }
}
