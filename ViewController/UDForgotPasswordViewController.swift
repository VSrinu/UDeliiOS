//
//  UDForgotPasswordViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 8/6/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDForgotPasswordViewController: UIViewController {
    @IBOutlet weak var mobileNumberTxt: ErrorTextField!
    @IBOutlet weak var newPasswordTxt: ErrorTextField!
    @IBOutlet weak var confirmPasswordTxt: ErrorTextField!
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
    }
    
    func setTextView() {
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: mobileNumberTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: newPasswordTxt)
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: confirmPasswordTxt)
    }
    
    func resetPassword() {
        view.endEditing(true)
        // MARK:- Phone Number
        let checkPhoneNumber = ConstantTools.sharedConstantTool.isValidMobileNumber(phoneNumber: mobileNumberTxt.text!)
        if !checkPhoneNumber {
            self.view.makeToast("Use vaild phone number only", position: .top)
            return
        }
        
        // MARK:- Password
        let newPassword = (newPasswordTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(newPassword.count == 0) {
            self.view.makeToast("Enter your New Password", position: .top)
            return
        }
        
        if (newPassword.count < 3) || (newPassword.count > 20) {
            self.view.makeToast("password must be 3 to 20 character", position: .top)
            return
        }
        
        let confirmPassword = (self.confirmPasswordTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if newPassword != confirmPassword {
            self.view.makeToast("Password does not match. Please check your password", position: .top)
            return
        }
        
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your password")
        ForgotPasswordModel.forgotPassword(mobileNumber: mobileNumberTxt.text!, newPassword: confirmPassword) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    if data != [:] {
                        self.getAlert()
                    } else {
                        self.view.makeToast("Please try later", position: .top)
                    }
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func getAlert() {
        self.present(UIAlertController.alertWithTitle(title: "", message: "Your password has been reset. Please remember to Logout and log back in.", cancelButtonTitle: "OK"), animated: true)
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToResetPassword(_ sender: Any) {
        resetPassword()
    }
    
    @IBAction func tapToNavigateBack(_ sender: Any) {
        self.navigationController!.popViewController(animated: true)
    }
}

// MARK:- TextFieldDelegates
extension UDForgotPasswordViewController:UITextFieldDelegate {
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

