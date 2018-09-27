//
//  UDLoginViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 6/22/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDLoginViewController: UIViewController {
    @IBOutlet weak var phoneTxt: ErrorTextField!
    @IBOutlet weak var passwordTxt: ErrorTextField!
    var customDelegate: UDCustomViewControllerDelegates?
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
    }
    
    func setTextView() {
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: phoneTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: passwordTxt)
    }
    
    func loginCheck() {
        view.endEditing(true)
        // MARK:- Phone Number
        let checkPhoneNumber = ConstantTools.sharedConstantTool.isValidMobileNumber(phoneNumber: phoneTxt.text!)
        if !checkPhoneNumber {
            self.view.makeToast("Use vaild phone number only", position: .top)
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
        
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        LoginModel.signIn(phoneNumber: phoneTxt.text!, password: password) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    UserDefaults.standard.set(true, forKey: "login")
                    userInfoDictionary.setValuesForKeys(data.firstObject as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    let userInfoDict = data.firstObject as? NSDictionary ?? [:]
                    let checkMerchantId = userInfoDict.object(forKey: "merchantid") as? Int ?? 0
                    if checkMerchantId != 0 {
                        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                        let viewController = storyboard.instantiateViewController(withIdentifier: "UDLandingViewController") as! UDLandingViewController
                        self.navigationController?.pushViewController(viewController, animated: true)
                    } else {
                        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                        let viewController = storyboard.instantiateViewController(withIdentifier: "UDWelcomeViewController") as! UDWelcomeViewController
                        self.navigationController?.pushViewController(viewController, animated: true)
                    }
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func navigateToLandingPage() {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDLandingViewController") as! UDLandingViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    func navigateToWelcomePage() {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDWelcomeViewController") as! UDWelcomeViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToSignIn(_ sender: Any) {
        loginCheck()
    }
    
    @IBAction func tapToSignUp(_ sender: Any) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDSignUpMobileViewController") as! UDSignUpMobileViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    @IBAction func tapToForgotPassword(_ sender: Any) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDForgotPasswordViewController") as! UDForgotPasswordViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

// MARK:- TextFieldDelegates
extension UDLoginViewController:UITextFieldDelegate {
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
