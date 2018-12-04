//
//  UDEditProfileViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 6/29/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDEditProfileViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    fileprivate var backButton: IconButton!
    var deatilsArray = NSArray()
    var firstName = String()
    var lastName = String()
    var emailId = String()
    var address = String()
    var city = String()
    var state = String()
    var zipCode = String()
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        self.loadInitialData()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    func loadInitialData() {
        prepareBackButton()
        prepareToolbar()
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        self.deatilsArray = [["title": "First Name", "details": "\(userInfoDictionary.object(forKey: "firstname") as? String ?? "")"], ["title": "Last Name", "details": "\(userInfoDictionary.object(forKey: "lastname") as? String ?? "")"],["title": "Email Id", "details": "\(userInfoDictionary.object(forKey: "emailid") as? String ?? "")"], ["title": "Address", "details": "\(userInfoDictionary.object(forKey: "address") as? String ?? "")"],["title": "City", "details": "\(userInfoDictionary.object(forKey: "city") as? String ?? "")"], ["title": "State", "details": "\(userInfoDictionary.object(forKey: "state") as? String ?? "")"], ["title":"Zip Code","details":"\(userInfoDictionary.object(forKey: "postalCodeLocation") as? String ?? "")"]]
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    @objc func textFieldEditing(_ textField: UITextField) {
        firstName = "\(textField.text ?? "")"
    }
    
    @objc func lastNameFieldEditing(_ textField: UITextField) {
        lastName = "\(textField.text ?? "")"
    }
    
    @objc func emailIdFieldEditing(_ textField: UITextField) {
        emailId = "\(textField.text ?? "")"
    }
    
    @objc func addressFieldEditing(_ textField: UITextField) {
        address = "\(textField.text ?? "")"
    }
    
    @objc func cityFieldEditing(_ textField: UITextField) {
        city = "\(textField.text ?? "")"
    }
    
    @objc func stateFieldEditing(_ textField: UITextField) {
        state = "\(textField.text ?? "")"
    }
    
    @objc func zipCodeFieldEditing(_ textField: UITextField) {
        zipCode = "\(textField.text ?? "")"
    }
    
    @IBAction func tapToUpdateProfile(_ sender: Any) {
        checkuserData()
    }
    
    func checkuserData() {
        let tableUserId = userInfoDictionary.object(forKey: "id") as? String ?? ""
        if firstName == "" {
            firstName = "\(userInfoDictionary.object(forKey: "firstname") as? String ?? "")"
        }
        
        if lastName == "" {
            lastName = "\(userInfoDictionary.object(forKey: "lastname") as? String ?? "")"
        }
        
        if emailId == "" {
            emailId = "\(userInfoDictionary.object(forKey: "emailid") as? String ?? "")"
        }
        
        if address == "" {
            address = "\(userInfoDictionary.object(forKey: "location") as? String ?? "")"
        }
        
        if city == "" {
            city = "\(userInfoDictionary.object(forKey: "city") as? String ?? "")"
        }
        
        if state == "" {
            state = "\(userInfoDictionary.object(forKey: "state") as? String ?? "")"
        }
        
        if zipCode == "" {
            zipCode = "\(userInfoDictionary.object(forKey: "zip") as? String ?? "")"
        }
        
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        ProfileUpdateModel.updateprofile(fName: firstName, lName: lastName, emailId: emailId, address: address, city: city, state: state, zipcode: zipCode, userId: tableUserId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    self.navigationController!.popViewController(animated: true) 
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
}

// MARK:- ToolBar
extension UDEditProfileViewController {
    fileprivate func prepareBackButton() {
        backButton = IconButton(image: Icon.cm.arrowBack, tintColor: .white)
        backButton.pulseColor = .white
        backButton.addTarget(self, action: #selector(navigateBack(button:)), for: .touchUpInside)
    }
    
    fileprivate func prepareToolbar() {
        toolBar.titleLabel.textColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
        toolBar.titleLabel.textAlignment = .left
        toolBar.leftViews = [backButton]
    }
    
    @objc
    fileprivate func navigateBack(button: UIButton) {
        self.navigationController!.popViewController(animated: true)
    }
}

// MARK:- UITableViewDataSource
extension UDEditProfileViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return deatilsArray.count
    }          
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "editProfileCell", for: indexPath) as! UDEditProfileTableViewCell
        cell.pulseAnimation = .none
        let detailsDict:NSDictionary = deatilsArray[indexPath.row] as! NSDictionary
        let title = detailsDict.object(forKey: "title") as? String ?? ""
        cell.titleLabel.text = title
        cell.textField.text = detailsDict.object(forKey: "details") as? String ?? ""
        cell.textField.delegate = self
        cell.textField.tag = indexPath.row
        switch indexPath.row {
        case 0:
            cell.textField.addTarget(self, action: #selector(self.textFieldEditing(_:)), for: .editingChanged)
        case 1:
            cell.textField.addTarget(self, action: #selector(self.lastNameFieldEditing(_:)), for: .editingChanged)
        case 2:
            cell.textField.addTarget(self, action: #selector(self.emailIdFieldEditing(_:)), for: .editingChanged)
        case 3:
            cell.textField.addTarget(self, action: #selector(self.addressFieldEditing(_:)), for: .editingChanged)
        case 4:
            cell.textField.addTarget(self, action: #selector(self.cityFieldEditing(_:)), for: .editingChanged)
        case 5:
            cell.textField.addTarget(self, action: #selector(self.stateFieldEditing(_:)), for: .editingChanged)
        case 6:
            cell.textField.addTarget(self, action: #selector(self.zipCodeFieldEditing(_:)), for: .editingChanged)
        default:
            break
        }
        return cell
    }
}

// MARK:- TextFieldDelegates
extension UDEditProfileViewController:UITextFieldDelegate {
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
