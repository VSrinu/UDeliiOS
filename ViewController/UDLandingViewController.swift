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
import FoldingCell
import CoreLocation

class UDLandingViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var noDataLabel: UILabel!
    fileprivate var menuButton: IconButton!
    fileprivate var notificationButton: IconButton!
    fileprivate var moreButton: IconButton!
    let refreshControl = UIRefreshControl()
    let kCloseCellHeight: CGFloat = 179
    let kOpenCellHeight: CGFloat = 488
    var cellHeights: [CGFloat] = []
    var jobListArray = NSArray()
    var distancefromstore = Double()
    override func viewDidLoad() {
        super.viewDidLoad()
        setNeedsStatusBarAppearanceUpdate()
        loadInitialData()
        setupSideMenu()
    }
    
    // MARK:- View Lifecycle
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        getUserData()
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        distancefromstore = Double(userInfoDictionary.object(forKey: "distancefromstore") as? Int ?? 0)
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
                        self.tableView.isHidden = true
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
                    let orderlistArray = data
                    let userDistance = self.distancefromstore.milesToKilometers()
                    if userDistance == 0.0 {
                        self.jobListArray = orderlistArray
                    } else {
                        let predicate = NSPredicate(format: "storetocustlocation <= %f", userDistance)
                        let newList = orderlistArray.filtered(using: predicate)
                        self.jobListArray = newList as NSArray
                    }
                    let descriptor: NSSortDescriptor =  NSSortDescriptor(key: "createdAt", ascending: true, selector: nil)
                    self.jobListArray = self.jobListArray.sortedArray(using: [descriptor]) as NSArray
                    self.tableReload(jobListArray:self.jobListArray)
                case .failure(let error):
                    self.noDataLabel.isHidden = false
                    self.tableView.isHidden = true
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func tableReload(jobListArray:NSArray) {
        if jobListArray.count == 0 {
            self.noDataLabel.isHidden = false
            self.tableView.isHidden = true
        } else {
            self.setup()
            self.noDataLabel.isHidden = true
            self.tableView.isHidden = false
            self.tableView.reloadData()
        }
    }
    
    private func setup() {
        cellHeights = Array(repeating: kCloseCellHeight, count: jobListArray.count)
        self.tableView.estimatedRowHeight = kCloseCellHeight
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
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return jobListArray.count
    }
    
    internal func tableView(_: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
        guard case let cell as UDLandingCell = cell else {
            return
        }
        cell.backgroundColor = .clear
        cell.requestedDeadline.isHidden = true
        cell.requestedDeadLineLabel.isHidden = true
        cellHeights[indexPath.row] == kCloseCellHeight ? cell.unfold(false, animated: false, completion: nil) : cell.unfold(true, animated: false, completion: nil)
        let jobDict:NSDictionary = jobListArray[indexPath.row] as! NSDictionary
        let orderId = jobDict.object(forKey: "orderid") as? Int ?? 0
        cell.jobId.text = "JOB ID \n\(orderId)"
        let preferreddeliverytime = jobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
        let deliverDate = ConstantTools.sharedConstantTool.dateFormate(date: preferreddeliverytime)
        cell.deliveryDate.text = deliverDate
        cell.envelopDeliveryDate.text = deliverDate
        let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
        cell.deliveryTime.text = time
        let customerName = jobDict.object(forKey: "customername") as? String ?? ""
        cell.jobTitle.text = customerName
        cell.customerName.text = customerName
        let numberofbags = jobDict.object(forKey: "numberofbags") as? Int ?? 0
        cell.noOfBags.text = "\(numberofbags)"
        let totalweight = jobDict.object(forKey: "totalweight") as? Int ?? 0
        cell.bagsKG.text = "\(totalweight) KG"
        let city = jobDict.object(forKey: "city") as? String ?? ""
        let state = jobDict.object(forKey: "state") as? String ?? ""
        let zip = jobDict.object(forKey: "zip") as? String ?? ""
        let address = "\(city),\(state),\(zip)"
        cell.address.text = address
        let totalitems = jobDict.object(forKey: "totalitems") as? Int ?? 0
        let perishable = jobDict.object(forKey: "perishable") as? Bool ?? false
        let fragile = jobDict.object(forKey: "fragile") as? Bool ?? false
        var isperishable = String()
        var isfragile = String()
        perishable == true ? (isperishable = "YES") : (isperishable = "NO")
        fragile == true ? (isfragile = "YES") : (isfragile = "NO")
        cell.orderDetails.text = "Total items \(totalitems) Fragile: \(isfragile) Perishable: \(isperishable)"
        ConstantTools.sharedConstantTool.getCoordinate(address: address, mapView: cell.mapView,customerName:address)
        cell.viewDetailsBtn.tag = indexPath.row
        cell.viewDetailsBtn.addTarget(self, action: #selector(tapToNavigateToViewDetails(button:)), for: .touchUpInside)
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "FoldingCell", for: indexPath) as! FoldingCell
        let durations: [TimeInterval] = [0.26, 0.2, 0.2]
        cell.durationsForExpandedState = durations
        cell.durationsForCollapsedState = durations
        return cell
    }
    
    internal func tableView(_: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return cellHeights[indexPath.row]
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 10
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let cell = tableView.cellForRow(at: indexPath) as! FoldingCell
        if cell.isAnimating() {
            return
        }
        var duration = 0.0
        let cellIsCollapsed = cellHeights[indexPath.row] == kCloseCellHeight
        if cellIsCollapsed {
            cellHeights[indexPath.row] = kOpenCellHeight
            cell.unfold(true, animated: true, completion: nil)
            duration = 0.5
        } else {
            cellHeights[indexPath.row] = kCloseCellHeight
            cell.unfold(false, animated: true, completion: nil)
            duration = 0.8
        }
        
        UIView.animate(withDuration: duration, delay: 0, options: .curveEaseOut, animations: { () -> Void in
            tableView.beginUpdates()
            tableView.endUpdates()
        }, completion: nil)
    }
    
    @objc
    fileprivate func tapToNavigateToViewDetails(button: UIButton) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDJobDetailsViewController") as! UDJobDetailsViewController
        let jobDict:NSDictionary = jobListArray[button.tag] as! NSDictionary
        viewController.jobDict = jobDict
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}
