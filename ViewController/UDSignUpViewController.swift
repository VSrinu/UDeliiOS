//
//  UDSignUpViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 6/22/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import Toast_Swift

class UDSignUpViewController: UIViewController {
    @IBOutlet weak var firstNameTxt: ErrorTextField!
    @IBOutlet weak var LastNameTxt: ErrorTextField!
    @IBOutlet weak var emailIdTxt: ErrorTextField!
    @IBOutlet weak var passwordTxt: ErrorTextField!
    @IBOutlet weak var confirmPassword: ErrorTextField!
    var phoneNumber = String()
    override func viewDidLoad() {
        super.viewDidLoad()
        loadInitialData()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
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
    }
    
    func setDeviceDetails() {
        let userData = UserDefaults.standard.object(forKey:"userInfo") as? Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: userData!) as! NSMutableDictionary?)!
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
        
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        SignUpModel.signUp(fName: fName, lName: lName, phoneNumber: phoneNumber, password: confirmPassword, emailId: emailIdTxt.text!, address: userInfoDictionary.object(forKey: "location") as? String ?? "", city: userInfoDictionary.object(forKey: "cityLocation") as? String ?? "", state: userInfoDictionary.object(forKey: "stateLocation") as? String ?? "", zip: userInfoDictionary.object(forKey: "postalCodeLocation") as? String ?? "", userDetails: userInfoDictionary, devicePlatform: userInfoDictionary.object(forKey: "systemname") as? String ?? "iOS", deviceToken: userInfoDictionary.object(forKey: "devicetoken") as? String ?? "", deviceUuid: userInfoDictionary.object(forKey: "deviceid") as? String ?? "", deviceVersion: userInfoDictionary.object(forKey: "systemversion") as! String, deviceName: userInfoDictionary.object(forKey: "name") as? String ?? "", deviceModel: userInfoDictionary.object(forKey: "model") as? String ?? "", appVersion: userInfoDictionary.object(forKey: "appVersion") as? String ?? "") { connectionResult in
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
