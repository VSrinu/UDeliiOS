//
//  UDLandingViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import SideMenu
import CoreLocation
import EnRouteApi

class UDLandingViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var noDataLabel: UILabel!
    @IBOutlet weak var switchStateLabel: UILabel!
    fileprivate var menuButton: IconButton!
    let refreshControl = UIRefreshControl()
    var SwitchControl = Switch()
    var jobListArray = NSArray()
    var glympseUsername = String()
    var glympsePwd = String()
    var profilestatus = String()
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        getGlympseUserDetails()
        loadInitialData()
        setupSideMenu()
        DispatchQueue.main.async {
            self.updateDeviceToken()
        }
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        DispatchQueue.main.async {
            ConstantTools.sharedConstantTool.getCurrentLocation()
        }
        getGlympseUserDetails()
        if glympseUsername != "" && glympsePwd != "" {
            EnRouteWrapper.instance.manager()?.overrideLoggingLevels(GlyCoreConstants.none(), debugLogLevel: GlyCoreConstants.info())
            EnRouteWrapper.instance.manager()?.add(self)
            EnRouteWrapper.instance.manager()?.setAuthenticationMode(GlyEnRouteConstants.auth_MODE_CREDENTIALS())
            EnRouteWrapper.instance.manager()?.start()
        }
        jobListArray = []
        getUserData()
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        profilestatus = userInfoDictionary.object(forKey: "profilestatus") as? String ?? "0"
        checkProfileUpdate()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    func loadInitialData() {
        prepareMenuButton()
        prepareSwitchButton()
        prepareToolbar()
        refreshControl.addTarget(self, action: #selector(didPullToRefresh), for: .valueChanged)
        self.tableView.addSubview(refreshControl)
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "fetching your job details")
    }
    
    @objc func didPullToRefresh() {
        getJobList()
    }
    
    func setupSideMenu() {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDSidePanelViewController") as! UDSidePanelViewController
        let menuLeftNavigationController = UISideMenuNavigationController(rootViewController: viewController)
        menuLeftNavigationController.navigationBar.isHidden = true
        SideMenuManager.default.menuLeftNavigationController = menuLeftNavigationController
        SideMenuManager.default.menuPresentMode = .menuSlideIn
        SideMenuManager.default.menuWidth = view.frame.width * CGFloat(0.656966)
        let styles:[UIBlurEffect.Style] = [.dark, .light, .extraLight]
        SideMenuManager.default.menuBlurEffectStyle = styles[2]
    }
    
    func checkProfileUpdate() {
        let merchantId = userInfoDictionary.object(forKey: "merchantid") as? Int ?? 0
        if merchantId == 0 {
            getAlert()
        }
    }
    
    func getAlert() {
        self.present(UIAlertController.alertWithTitle(title: "", message: "Update Your profile to get Jobs form your merchant", buttonTitle: "OK", handler: { action in self.tapToProfile()}), animated: true)
    }
    
    func tapToProfile() {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDProfileViewController") as! UDProfileViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
    
    func getUserData() {
        ProfileUpdateModel.getUserDetails(userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
                    userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
                    let isCarrireActive = userInfoDictionary.object(forKey: "active") as? String ?? ""
                    if isCarrireActive != "1" {
                        ConstantTools.sharedConstantTool.hideMRIndicatorView()
                        self.getUserAlert()
                        self.noDataLabel.isHidden = false
                        self.noDataLabel.text = "Your Merchant have not approved to start the job."
                        self.tableView.isHidden = true
                        return
                    } else {
                        self.tableView.isHidden = false
                        //self.noDataLabel.isHidden = true
                        self.getJobList()
                    }
                case .failure(let error):
                    ConstantTools.sharedConstantTool.hideMRIndicatorView()
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func getUserAlert() {
        self.present(UIAlertController.alertWithTitle(title: "Merchant Approve", message: "Your request for participating as a Carrier with Merchant is currently being reviewed by the Merchant. We are very excited for you and thankyou very much for your patience. We will update you as soon as the review is complete.", buttonTitle: "OK"), animated: true)
    }
    
    func updateDeviceToken() {
        let deviceToken = userInfoDictionary.object(forKey: "newDevicetoken") as? String ?? ""
        ProfileUpdateModel.updateDeviceToken(devicetoken: deviceToken, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
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
    
    func getJobList() {
        let isCarrireActive = userInfoDictionary.object(forKey: "active") as? String ?? ""
        if isCarrireActive != "1" {
            ConstantTools.sharedConstantTool.hideMRIndicatorView()
            return
        }
        let merchantId = userInfoDictionary.object(forKey: "merchantid") as? Int ?? 0
        let userId = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
        OrdersModel.getOrdersDetails(acceptedby: userId, merchantId: merchantId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                self.refreshControl.endRefreshing()
                switch connectionResult {
                case .success(let data):
                    self.jobListArray = data as NSArray
                    let descriptor: NSSortDescriptor =  NSSortDescriptor(key: "createdAt", ascending: true, selector: nil)
                    self.jobListArray = self.jobListArray.sortedArray(using: [descriptor]) as NSArray
                    self.tableReload(jobListArray:self.jobListArray)
                case .failure(let error):
                    self.noDataLabel.isHidden = false
                    self.view.makeToast(error, position: .top)
                    self.tableView.reloadData()
                }
            })
        }
    }
    
    func tableReload(jobListArray:NSArray) {
        if jobListArray.count == 0 {
            self.noDataLabel.isHidden = false
            //self.tableView.isHidden = true
        } else {
            self.setup()
            self.noDataLabel.isHidden = true
            //self.tableView.isHidden = false
        }
    }
    
    private func setup() {
        self.tableView.backgroundColor = #colorLiteral(red: 0, green: 0.7254901961, blue: 0.8980392157, alpha: 0.09754922945)
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    // MARK:- Target Action Buttons
    @objc
    fileprivate func tapToOpenSidePanel(button: UIButton) {
        present(SideMenuManager.default.menuLeftNavigationController!, animated: true, completion: nil)
    }
    
    @objc
    fileprivate func tapToNavigateToProfile(button: UIButton) {
        tapToProfile()
    }
    
    @objc
    fileprivate func navigateNotification(button: UIButton) {
        print("notification")
    }
}

// MARK:- ToolBar
extension UDLandingViewController {
    fileprivate func prepareMenuButton() {
        menuButton = IconButton(image: Icon.cm.menu, tintColor: .white)
        menuButton.pulseColor = .white
        menuButton.addTarget(self, action: #selector(tapToOpenSidePanel(button:)), for: .touchUpInside)
    }
    
    fileprivate func prepareSwitchButton() {
        if profilestatus == "0" {
            SwitchControl = Switch(state: .off, style: .dark, size: .large)
        } else {
            SwitchControl = Switch(state: .on, style: .dark, size: .large)
        }
        SwitchControl.buttonOnColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
        SwitchControl.trackOnColor = #colorLiteral(red: 0.1451823844, green: 0.9490196078, blue: 0.2762260474, alpha: 1)
        SwitchControl.delegate = self
    }
    
    fileprivate func prepareToolbar() {
        toolBar.titleLabel.textColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
        toolBar.titleLabel.textAlignment = .left
        toolBar.rightViews = [SwitchControl]
        toolBar.leftViews = [menuButton]
    }
}

// MARK:- UITableViewDataSource
extension UDLandingViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return jobListArray.count
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        if section == 0 {
            return 6
        }
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "jobCell", for: indexPath) as! UDLandingCell
        let jobDict:NSDictionary = jobListArray[indexPath.row] as! NSDictionary
        let orderId = jobDict.object(forKey: "orderid") as? Int ?? 0
        cell.jobIdLabel.text = "\(orderId)"
        let preferreddeliverytime = jobDict.object(forKey: "preferreddeliverytimeoffset") as? Date ?? Date()
        let deliverDate = ConstantTools.sharedConstantTool.dayFormat(date: preferreddeliverytime)
        cell.deliveryDate.text = deliverDate
        let deliverMonth = ConstantTools.sharedConstantTool.monthFormat(date: preferreddeliverytime)
        cell.deliveryMonth.text = deliverMonth
        let time = ConstantTools.sharedConstantTool.timeFormat(date: preferreddeliverytime)
        cell.deliveryTime.text = time
        let customerName = jobDict.object(forKey: "customername") as? String ?? ""
        let city = jobDict.object(forKey: "city") as? String ?? ""
        cell.jobDetails.text = "Deliver to \(customerName) at \(city)"
        cell.distanceFromStore.text = "From Store: \(jobDict.object(forKey: "storetocustlocation") as? Double ?? 0.0) Miles"
        cell.distanceFromeAddress.text = "From your Address: \(jobDict.object(forKey: "carriertocustlocation") as? Double ?? 0.0) Miles"
        cell.activeCarriers.text = "# of Active Carriers: \(jobDict.object(forKey: "carriercount") as? Int ?? 0)"
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let jobDict:NSDictionary = jobListArray[indexPath.row] as! NSDictionary
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDJobDetailsViewController") as! UDJobDetailsViewController
        viewController.jobDict = jobDict
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

// MARK:- Glympse
extension UDLandingViewController {
    func getGlympseUserDetails()  {
        glympseUsername = userInfoDictionary.object(forKey: "glympseusername") as? String ?? ""
        glympsePwd = userInfoDictionary.object(forKey: "glympsepwd") as? String ?? ""
    }
}

// MARK:- GlyListener
extension UDLandingViewController: GlyListener {
    func eventsOccurred(_ source: GlySource!, listener: Int32, events: Int32, param1: GlyCommon!, param2: GlyCommon!) {
        if GlyEnRouteEvents.listener_ENROUTE_MANAGER() == listener {
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_STARTED() ) {
                print("En Route Event: ENROUTE_MANAGER_STARTED")
            }
            
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_AUTHENTICATION_NEEDED() ) {
                handleLogin()
            }
            
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_LOGIN_COMPLETED() ) {
                print("En Route Event: ENROUTE_MANAGER_LOGIN_COMPLETED")
            }
            
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_SYNCED() ) {
                print("En Route Event: ENROUTE_MANAGER_SYNCED")
            }
            
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_LOGGED_OUT() ) {
                print("En Route Event: ENROUTE_MANAGER_LOGGED_OUT")
                
            }
            
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_STOPPED() ) {
                print("En Route Event: ENROUTE_MANAGER_STOPPED")
                handleStopped()
            }
        }
    }
    
    func handleStopped() {
        EnRouteWrapper.instance.manager()?.overrideLoggingLevels(GlyCoreConstants.none(), debugLogLevel: GlyCoreConstants.info())
        EnRouteWrapper.instance.manager()?.add(self)
        EnRouteWrapper.instance.manager()?.setAuthenticationMode(GlyEnRouteConstants.auth_MODE_CREDENTIALS())
        EnRouteWrapper.instance.manager()?.start()
    }
    
    /*func handleStopped() {
     self.present(UIAlertController.alertWithTitle(title: "", message: "Invalid credentials, please try again.", buttonTitle: "OK", handler: { action in self.tapToLogOut()}), animated: true)
     }*/
    
    func tapToLogOut() {
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
    
    func handleLogin() {
        EnRouteWrapper.instance.manager()?.login(withCredentials: glympseUsername, password: glympsePwd)
    }
}

extension UDLandingViewController: SwitchDelegate {
    func switchDidChangeState(control: Switch, state: SwitchState) {
        .on == state ? updateStatus(state: 1) : updateStatus(state: 0)
    }
    
    func updateStatus(state:Int) {
        if state == 0 {
            switchStateLabel.text = "offline"
        } else {
            switchStateLabel.text = "online"
        }
        ProfileUpdateModel.updateStatus(profileStatus: state, userId: userInfoDictionary.object(forKey: "id") as? String ?? "") { connectionResult in
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
}
