//
//  UDLandingViewController.swift
//  UDeli
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
    fileprivate var menuButton: IconButton!
    fileprivate var notificationButton: IconButton!
    fileprivate var moreButton: IconButton!
    let refreshControl = UIRefreshControl()
    var jobListArray = NSArray()
    var glympseUsername = String()
    var glympsePwd = String()
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        loadInitialData()
        setupSideMenu()
        getGlympseUserDetails()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        EnRouteWrapper.instance.manager()?.overrideLoggingLevels(GlyCoreConstants.none(), debugLogLevel: GlyCoreConstants.info())
        EnRouteWrapper.instance.manager()?.add(self)
        EnRouteWrapper.instance.manager()?.setAuthenticationMode(GlyEnRouteConstants.auth_MODE_CREDENTIALS())
        EnRouteWrapper.instance.manager()?.start()
        getUserData()
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        checkProfileUpdate()
        getJobList()
    }
    
    override var preferredStatusBarStyle: UIStatusBarStyle {
        return .lightContent
    }
    
    func loadInitialData() {
        prepareMoreButton()
        prepareMenuButton()
        preparenotificationButton()
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
                        self.getUserAlert()
                        self.noDataLabel.isHidden = false
                        self.noDataLabel.text = "Your Merchant have not approved to start the job."
                        return
                    }
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func getUserAlert() {
        self.present(UIAlertController.alertWithTitle(title: "Merchant Approve", message: "Your Merchant have not approved to start the job. Please Contact your merchant to approve or further details", buttonTitle: "OK"), animated: true)
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
                }
            })
        }
    }
    
    func tableReload(jobListArray:NSArray) {
        if jobListArray.count == 0 {
            self.noDataLabel.isHidden = false
            self.tableView.reloadData()
        } else {
            self.setup()
            self.noDataLabel.isHidden = true
            self.tableView.isHidden = false
            self.tableView.reloadData()
        }
    }
    
    private func setup() {
        self.tableView.backgroundColor = #colorLiteral(red: 0, green: 0.7254901961, blue: 0.8980392157, alpha: 0.09754922945)
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.tableFooterView = UIView()
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
    fileprivate func prepareMoreButton() {
        moreButton = IconButton(image: Icon.cm.moreVertical, tintColor: .white)
        moreButton.pulseColor = .white
        moreButton.addTarget(self, action: #selector(tapToNavigateToProfile(button:)), for: .touchUpInside)
    }
    
    fileprivate func prepareMenuButton() {
        menuButton = IconButton(image: Icon.cm.menu, tintColor: .white)
        menuButton.pulseColor = .white
        menuButton.addTarget(self, action: #selector(tapToOpenSidePanel(button:)), for: .touchUpInside)
    }
    
    fileprivate func preparenotificationButton() {
        notificationButton = IconButton(image: Icon.cm.bell, tintColor: .white)
        notificationButton.pulseColor = .white
        notificationButton.addTarget(self, action: #selector(navigateNotification(button:)), for: .touchUpInside)
    }
    
    fileprivate func prepareToolbar() {
        toolBar.titleLabel.textColor = #colorLiteral(red: 1, green: 1, blue: 1, alpha: 1)
        toolBar.titleLabel.textAlignment = .left
        toolBar.rightViews = [notificationButton,moreButton]
        toolBar.leftViews = [menuButton]
    }
}

// MARK:- UITableViewDataSource
extension UDLandingViewController: UITableViewDataSource, UITableViewDelegate {
    internal func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
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
        let preferreddeliverytime = jobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
        let deliverDate = ConstantTools.sharedConstantTool.dayFormate(date: preferreddeliverytime)
        cell.deliveryDate.text = deliverDate
        let deliverMonth = ConstantTools.sharedConstantTool.mothFormate(date: preferreddeliverytime)
        cell.deliveryMonth.text = deliverMonth
        let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
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
        getOrginalOrders(OrderId:jobDict.object(forKey: "orderid") as? Int ?? 0)
    }
    
    func getOrginalOrders(OrderId: Int) {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        OrdersModel.getSingleOrdersDetails(orderid: OrderId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                self.refreshControl.endRefreshing()
                switch connectionResult {
                case .success(let data):
                    let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
                    let viewController = storyboard.instantiateViewController(withIdentifier: "UDJobDetailsViewController") as! UDJobDetailsViewController
                    viewController.jobDict = data
                    self.navigationController?.pushViewController(viewController, animated: true)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
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
                print("En Route Event: ENROUTE_MANAGER_AUTHENTICATION_NEEDED")
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
    
    func handleLogin() {
        EnRouteWrapper.instance.manager()?.login(withCredentials: glympseUsername, password: glympsePwd)
    }
}
