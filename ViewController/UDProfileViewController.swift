//
//  UDProfileViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material

class UDProfileViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var profileImage: DesignableImageView!
    @IBOutlet weak var nameLabel: UILabel!
    var deatilsArray = NSArray()
    let imagePicker = UIImagePickerController()
    override func viewDidLoad() {
        super.viewDidLoad()
        loadTableView()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        loadInitialData()
    }
    
    func loadTableView() {
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
    }
    
    func loadInitialData() {
        DispatchQueue.main.async {
            let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
            userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
            self.setProfileData()
            let notificationtype = userInfoDictionary.object(forKey: "notificationtype") as? Int ?? 0
            NotificationTypeId = NotificationType(rawValue: notificationtype)!
            self.deatilsArray = [["title": "First Name", "details": "\(userInfoDictionary.object(forKey: "firstname") as? String ?? "")"], ["title": "Last Name", "details": "\(userInfoDictionary.object(forKey: "lastname") as? String ?? "")"], ["title": "Mobile Number", "details": "\(userInfoDictionary.object(forKey: "phonenumber") as? String ?? "")"], ["title": "Email Id", "details": "\(userInfoDictionary.object(forKey: "emailid") as? String ?? "")"], ["title": "Address", "details": "\(userInfoDictionary.object(forKey: "address") as? String ?? "")"],["title": "City", "details": "\(userInfoDictionary.object(forKey: "city") as? String ?? "")"], ["title": "State", "details": "\(userInfoDictionary.object(forKey: "state") as? String ?? "")"], ["title":"Zip Code","details":"\(userInfoDictionary.object(forKey: "postalCodeLocation") as? String ?? "")"], ["title": "Password", "details": "*******"]]
            self.tableView.reloadData()
        }
    }
    
    func setProfileData() {
        self.nameLabel.text = userInfoDictionary.object(forKey: "firstname") as? String ?? ""
        let profileData = userInfoDictionary.object(forKey: "profileimage") as? String ?? ""
        if profileData != "" {
            let dataDecoded : Data = Data(base64Encoded: profileData, options: .ignoreUnknownCharacters)!
            let decodedimage:UIImage = UIImage(data: dataDecoded as Data)!
            self.profileImage.image = decodedimage
        }
    }
    
    @objc func switchValueDidChange(_ sender: UISwitch) {
        var profileStatus = Int()
        switch sender.isOn {
        case false:
            profileStatus = 0
        case true:
            profileStatus = 1
        }
        ProfileUpdateModel.updateStatus(profileStatus: profileStatus, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    //MARK: - Open the camera
    func openCamera(){
        if(UIImagePickerController .isSourceTypeAvailable(UIImagePickerController.SourceType.camera)){
            imagePicker.sourceType = UIImagePickerController.SourceType.camera
            imagePicker.allowsEditing = true
            imagePicker.delegate = self
            self.present(imagePicker, animated: true, completion: nil)
        }
        else{
            let alert  = UIAlertController(title: "Warning", message: "You don't have camera", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        }
    }
    
    //MARK: - Choose image from camera roll
    func openGallary(){
        imagePicker.sourceType = UIImagePickerController.SourceType.photoLibrary
        //If you dont want to edit the photo then you can set allowsEditing to false
        imagePicker.allowsEditing = true
        imagePicker.delegate = self
        self.present(imagePicker, animated: true, completion: nil)
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToNavigateBack(_ sender: Any) {
        self.navigationController!.popViewController(animated: true)
    }
    
    @IBAction func tapToSelectProfileImage(_ sender: Any) {
        let alert = UIAlertController(title: nil, message: nil, preferredStyle: .actionSheet)
        alert.addAction(UIAlertAction(title: "Take Photo", style: .default, handler: { _ in
            self.openCamera()
        }))
        
        alert.addAction(UIAlertAction(title: "Choose Photo", style: .default, handler: { _ in
            self.openGallary()
        }))
        
        alert.addAction(UIAlertAction.init(title: "Cancel", style: .cancel, handler: nil))
        //If you want work actionsheet on ipad then you have to use popoverPresentationController to present the actionsheet, otherwise app will crash in iPad
        switch UIDevice.current.userInterfaceIdiom {
        case .pad:
            alert.popoverPresentationController?.sourceView = sender as? UIView
            alert.popoverPresentationController?.sourceRect = (sender as AnyObject).bounds
            alert.popoverPresentationController?.permittedArrowDirections = .up
        default:
            break
        }
        self.present(alert, animated: true, completion: nil)
    }
    
    @IBAction func tapToEdit(_ sender: Any) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDEditProfileViewController") as! UDEditProfileViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

// MARK:- UITableViewDataSource
extension UDProfileViewController: UITableViewDataSource, UITableViewDelegate {
    internal func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }
    
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if section == 0 {
            return deatilsArray.count
        } else {
            return 1
        }
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 30
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        if section == 0 {
            return "Private Information"
        } else {
            return "Settings"
        } 
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        switch indexPath.section {
        case 0:
            let cell = tableView.dequeueReusableCell(withIdentifier: "ProfileCell", for: indexPath) as! UDProfileTableViewCell
            let detailsDict:NSDictionary = deatilsArray[indexPath.row] as! NSDictionary
            let title = detailsDict.object(forKey: "title") as? String ?? ""
            cell.titleLabel.text = title
            cell.detailsLabel.text = detailsDict.object(forKey: "details") as? String ?? ""
            return cell
        default:
            let cell = tableView.dequeueReusableCell(withIdentifier: "settingCell", for: indexPath) as! UDProfileTableViewCell
            cell.pulseAnimation = .none
            cell.customDelegate = self
            let profilestatus = userInfoDictionary.object(forKey: "profilestatus") as? String ?? "0"
            profilestatus == "0" || profilestatus == "" ? (cell.profileStatusSwitch.isOn = false) : (cell.profileStatusSwitch.isOn = true)
            cell.profileStatusSwitch.addTarget(self, action: #selector(switchValueDidChange(_:)), for: .valueChanged)
            cell.storeDistanceBtn.addTarget(self, action: #selector(selectStoreDistance(button:)), for: .touchUpInside)
            let distancefromstore = userInfoDictionary.object(forKey: "distancefromstore") as? Int ?? 0
            if distancefromstore != 0 {
                cell.storeDistanceBtn.title = "Distance from store to customer location: \(distancefromstore) mi"
            }
            switch NotificationTypeId {
            case .None:
                cell.emailRadioBtn.isSelected = false
                cell.mobileRadioBtn.isSelected = false
            case .ByText:
                cell.emailRadioBtn.isSelected = false
                cell.mobileRadioBtn.isSelected = true
            case .ByEmail:
                cell.emailRadioBtn.isSelected = true
                cell.mobileRadioBtn.isSelected = false
            }
            return cell
        }
    }
    
    @objc
    fileprivate func selectStoreDistance(button: UIButton) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDDistanceSelectViewController") as! UDDistanceSelectViewController
        viewController.pageTitle = "store"
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

//MARK: - UIImagePickerControllerDelegate
extension UDProfileViewController:  UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    private func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        if let editedImage = info[UIImagePickerController.InfoKey.editedImage] as? UIImage {
            let data = editedImage.jpegData(compressionQuality: 0.1)
            let image = UIImage(data: data!)
            self.profileImage.image = image
            DispatchQueue.global(qos:.userInteractive).async {
                let imageData = data?.base64EncodedString(options: .lineLength64Characters)
                self.updateProfileImage(data: imageData!)
            }
        }
        picker.dismiss(animated: true, completion: nil)
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true, completion: nil)
    }
    
    func updateProfileImage(data:String) {
        ProfileUpdateModel.updateprofileImage(image: data, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
                    userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
}

// MARK:- LGCustomViewControllerDelegates
extension UDProfileViewController: UDCustomViewControllerDelegates {
    func CustomCellUpdater(notificationType:Int) {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your settings")
        ProfileUpdateModel.updateNotificationType(notificationType: notificationType, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
                    userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
                    NotificationTypeId = NotificationType(rawValue: userInfoDictionary.object(forKey: "notificationtype") as? Int ?? 0)!
                    self.tableView.reloadSections([1,0], with: .fade)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
            
        }
    }
}
