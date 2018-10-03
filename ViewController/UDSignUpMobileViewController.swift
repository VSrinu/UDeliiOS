//
//  UDSignUpMobileViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 9/24/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDSignUpMobileViewController: UIViewController {
    @IBOutlet weak var mobileTxt: ErrorTextField!
    @IBOutlet weak var flageImage: UIImageView!
    @IBOutlet weak var countryBtn: UIButton!
    var countryArray = NSArray()
    var countryDict = NSDictionary()
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
        setCountryCode()
    }
    
    func setTextView() {
        ConstantTools.sharedConstantTool.setTextFieldColor(textField: mobileTxt)
    }
    
    func setDeviceDetails() {
        let userData = UserDefaults.standard.object(forKey:"userInfo") as? Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: userData!) as! NSMutableDictionary?)!
    }
    
    func setCountryCode() {
        countryArray = countryArray.countries()
        let currentCountryCode = userInfoDictionary.object(forKey: "countryCode") as? String ?? ""
        let predicate = NSPredicate(format: "code contains[c] %@", currentCountryCode)
        let newList = countryArray.filtered(using: predicate)
        countryDict = newList.first as? NSDictionary ?? [:]
        let imagePath = "CountryPicker.bundle/\(countryDict.object(forKey: "code") ?? "").png"
        flageImage.image = UIImage(named:imagePath)
        countryBtn.setTitle("\(countryDict.object(forKey: "dial_code") as? String ?? "") \u{25BE} ", for: .normal)
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToNavigateBack(_ sender: Any) {
        self.navigationController!.popViewController(animated: true)
    }
    
    @IBAction func tapToSelectCountry(_ sender: Any) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDCountryCodeViewController") as! UDCountryCodeViewController
        viewController.delegate = self
        self.present(viewController, animated: true, completion: nil)
    }
    
    @IBAction func tapToSignUp(_ sender: Any) {
        let checkPhoneNumber = ConstantTools.sharedConstantTool.isValidMobileNumber(phoneNumber: mobileTxt.text!)
        if !checkPhoneNumber {
            self.view.makeToast("Use vaild phone number only", position: .top)
            return
        }
        checkMobileNumber()
    }
    
    func checkMobileNumber() {
        view.endEditing(true)
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        SignUpModel.checkMobileNumber(phoneNumber: mobileTxt.text!) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    print(data)
                    let countryCode = self.countryDict.object(forKey: "dial_code") as? String ?? ""
                    let phoneNumber = self.mobileTxt.text ?? ""
                    VerifyAPI.sendVerificationCode(countryCode, phoneNumber)
                    let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                    let viewController = storyboard.instantiateViewController(withIdentifier: "UDMobileVerificationViewController") as! UDMobileVerificationViewController
                    viewController.countryCode = countryCode
                    viewController.phoneNumber = phoneNumber
                    self.navigationController?.pushViewController(viewController, animated: true)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
}

extension UDSignUpMobileViewController: UDCustomViewControllerDelegates {
    func countryCodeSelect(countryData:NSDictionary) {
        countryDict = countryData
        let imagePath = "CountryPicker.bundle/\(countryDict.object(forKey: "code") ?? "").png"
        flageImage.image = UIImage(named:imagePath)
        countryBtn.setTitle("\(countryDict.object(forKey: "dial_code") as? String ?? "") \u{25BE} ", for: .normal)
    }
}
