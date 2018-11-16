//
//  UDSidePanelViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 8/10/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import SideMenu
import EnRouteApi

class UDSidePanelViewController: UIViewController {
    @IBOutlet weak var userName: UILabel!
    @IBOutlet weak var userPhoneNumber: UILabel!
    @IBOutlet weak var tableView: UITableView!
    var settingsArray = NSArray()
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        loadTableView()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    override func viewWillAppear(_ animated: Bool) {
        loadInitialData()
    }
    
    func loadTableView() {
        self.settingsArray = [["icon": "ic_settings", "title": "Settings"],["icon": "ic_myJob", "title": "My Orders"],["icon": "ic_completedJobs", "title": "Completed Orders"],["icon": "ic_share", "title": "Share"], ["icon": "ic_feedBack", "title": "Feedback"], ["icon": "ic_aboutUs", "title": "About Us"], ["icon": "ic_logout", "title": "Log Out"]]
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    func loadInitialData() {
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        userName.text = userInfoDictionary.object(forKey: "firstname") as? String ?? ""
        userPhoneNumber.text = userInfoDictionary.object(forKey: "phonenumber") as? String ?? ""
    }
    
    func getLogoutAlert() {
        self.present(UIAlertController.alertWithTitle(title: "", message: "Logging out once in a while is a good thing. Are you sure you want to logout now?", cancelButtonTitle: "Cancel", buttonTitle: "Logout", handler: { action in self.tapToLogout()}), animated: true)
    }
    
    func tapToLogout() {
        EnRouteWrapper.instance.manager()?.logout(GlyEnRouteConstants.logout_REASON_USER_ACTION())
        resetUserValues()
        ConstantTools.sharedConstantTool.prepareDeviceInformation()
        ConstantTools.sharedConstantTool.getCurrentLocation()
        UIApplication.shared.registerForRemoteNotifications()
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let LGLoginView: UIViewController? = storyboard.instantiateViewController(withIdentifier: "UDLoginViewController")
        self.navigationController?.pushViewController(LGLoginView!, animated: true)
    }
    
    func resetUserValues() {
        UserDefaults.standard.set(false, forKey: "login")
        UserDefaults.standard.set(nil, forKey: "userInfo")
    }
}

// MARK:- UITableViewDataSource
extension UDSidePanelViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return settingsArray.count
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "sidePanelCell", for: indexPath) as! UDSettingTableViewCell
        let settingDict:NSDictionary = settingsArray[indexPath.row] as! NSDictionary
        cell.titleLabel.text = settingDict.object(forKey: "title") as? String ?? ""
        let icon = settingDict.object(forKey: "icon") as? String ?? ""
        cell.icon.image = UIImage(named: icon)
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        switch indexPath.row {
        case 0:
            let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
            let viewController = storyboard.instantiateViewController(withIdentifier: "UDProfileViewController") as! UDProfileViewController
            self.navigationController?.pushViewController(viewController, animated: true)
        case 1:
            let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
            let viewController = storyboard.instantiateViewController(withIdentifier: "UDMyOrdersViewController") as! UDMyOrdersViewController
            self.navigationController?.pushViewController(viewController, animated: true)
        case 2:
            let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
            let viewController = storyboard.instantiateViewController(withIdentifier: "UDCompletedJobsViewController") as! UDCompletedJobsViewController
            self.navigationController?.pushViewController(viewController, animated: true)
        case 3:
            print("share")
        case 4:
            print("Feedback")
        case 5:
            print("About Us")
        case 6:
            getLogoutAlert()
        default:
            break
        }
    }
}
