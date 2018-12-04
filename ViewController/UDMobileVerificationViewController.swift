//
//  UDMobileVerificationViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 9/24/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDMobileVerificationViewController: UIViewController {
    @IBOutlet weak var codeTxt: ErrorTextField!
    var countryCode = String()
    var phoneNumber = String()
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
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: codeTxt)
    }
    
    func setDeviceDetails() {
        let userData = UserDefaults.standard.object(forKey:"userInfo") as? Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: userData!) as! NSMutableDictionary?)!
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToNavigateBack(_ sender: Any) {
        self.navigationController!.popToRootViewController(animated: true)
    }
    
    @IBAction func tapToResendCode(_ sender: Any) {
        VerifyAPI.sendVerificationCode(countryCode, phoneNumber)
    }
    
    @IBAction func tapToSignUp(_ sender: Any) {
        let enterCode = (codeTxt.text?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines))!
        if(enterCode.count == 0) {
            self.view.makeToast("Enter your Code", position: .top)
            return
        }
        let code = codeTxt.text
        VerifyAPI.validateVerificationCode(countryCode, phoneNumber, code ?? "") { checked in
            if (checked.success) {
                let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                let viewController = storyboard.instantiateViewController(withIdentifier: "UDSignUpViewController") as! UDSignUpViewController
                viewController.phoneNumber = self.phoneNumber
                self.navigationController?.pushViewController(viewController, animated: true)
            } else {
                self.view.makeToast(checked.message, position: .top)
            }
        }
    }
}
