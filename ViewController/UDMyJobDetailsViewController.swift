//
//  UDMyJobDetailsViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 9/5/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import MapKit
import EnRouteApi

class UDMyJobDetailsViewController: UIViewController, GlyListener {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var tableView: UITableView!
    fileprivate var backButton: IconButton!
    var myJobDict = NSDictionary()
    var glympseUsername = String()
    var glympsePwd = String()
    var glympsetaskid = Int()
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
    
    override func viewWillAppear(_ animated: Bool) {
        getGlympseUserDetails()
        glympsetaskid = myJobDict.object(forKey: "glympsetaskid") as? Int ?? 0
        EnRouteWrapper.instance.manager()?.add(self)
        EnRouteWrapper.instance.manager()?.getTaskManager().add(self)
    }
    
    func getGlympseUserDetails()  {
        glympseUsername = userInfoDictionary.object(forKey: "glympseusername") as? String ?? ""
        glympsePwd = userInfoDictionary.object(forKey: "glympsepwd") as? String ?? ""
    }
    
    func loadInitialData() {
        prepareBackButton()
        prepareToolbar()
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    func eventsOccurred(_ source: GlySource!, listener: Int32, events: Int32, param1: GlyCommon!, param2: GlyCommon!) {
        if GlyEnRouteEvents.listener_ENROUTE_MANAGER() == listener {
            if 0 != ( events & GlyEnRouteEvents.enroute_MANAGER_LOGGED_OUT() ) {
                print("not login")
            }
        }
        else if GlyEnRouteEvents.listener_TASKS() == listener {
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_LIST_CHANGED() ) {
                print("update Task")
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_STARTED() ) {
                updateLiveTask()
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_TASK_START_FAILED() ) {
                self.present(UIAlertController.alertWithTitle(title: "", message: "unable to start job. Please contact merchant for the details.", cancelButtonTitle: "OK"), animated: true)
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_OPERATION_COMPLETED() ) {
                print("complete Task")
            }
            if 0 != ( events & GlyEnRouteEvents.tasks_OPERATION_COMPLETION_FAILED() ) {
                print("update Task")
            }
        }
    }
    
    // MARK:- Button Actions
    @objc
    fileprivate func tapToDirection(button: UIButton) {
        let address = myJobDict.object(forKey: "address") as? String ?? ""
        let city = myJobDict.object(forKey: "city") as? String ?? ""
        let state = myJobDict.object(forKey: "state") as? String ?? ""
        let zip = myJobDict.object(forKey: "zip") as? String ?? ""
        let fullAddress = "\(address)\(city),\(state),\(zip)"
        let geocoder = CLGeocoder()
        geocoder.geocodeAddressString(fullAddress) { (placemarks, error) in
            if error == nil {
                if let placemark = placemarks?[0] {
                    let location = placemark.location!
                    if (UIApplication.shared.canOpenURL(URL(string:"comgooglemaps://")!)) {
                        UIApplication.shared.open(URL(string:
                            "comgooglemaps://?saddr=&daddr=\(location.coordinate.latitude),\(location.coordinate.longitude)&views=transit")!, options: [:], completionHandler: nil)
                    } else {
                        UIApplication.shared.open(URL(string:
                            "https://www.google.co.in/maps/dir/?saddr=&daddr=\(location.coordinate.latitude),\(location.coordinate.longitude)&views=transit")!, options: [:], completionHandler: nil)
                    }
                    return
                }
            }
        }
    }
    
    @objc
    fileprivate func tapToAcceptJobs(button: UIButton) {
        if glympsetaskid == 0 {
            self.present(UIAlertController.alertWithTitle(title: "", message: "Your job in verify process. Please try later.", buttonTitle: "OK", handler: { action in self.updateLandingPage()}), animated: true)
            return
        }
        let task:GlyTask = (EnRouteWrapper.instance.manager()?.getTaskManager()?.findTask(byId: Int64(glympsetaskid)))!
        updateStartTask(task:task)
    }
    
    func updateStartTask(task:GlyTask) {
        EnRouteWrapper.instance.manager()?.getTaskManager().startTask(with: task)
    }
    
    func updateLiveTask() {
        let task:GlyTask = (EnRouteWrapper.instance.manager()?.getTaskManager()?.findTask(byId: Int64(glympsetaskid)))!
        EnRouteWrapper.instance.manager()?.getTaskManager().setTaskPhase(task, phase: GlyEnRouteConstants.phase_PROPERTY_LIVE())
        self.updateOrder(status: String(OrderStatusType.InProgress.rawValue))
    }
    
    @objc
    fileprivate func tapToComplete(button: UIButton) {
        let task:GlyTask = (EnRouteWrapper.instance.manager()?.getTaskManager()?.findTask(byId: Int64(glympsetaskid)))!
        let operation = task.getOperation()
        EnRouteWrapper.instance.manager()?.getTaskManager().complete(operation)
        self.updateOrder(status: String(OrderStatusType.Delivered.rawValue))
    }
    
    func updateOrder(status: String) {
        let orderId = myJobDict.object(forKey: "id") as? String ?? ""
        let acceptedby = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        OrdersModel.updateOrderStatus(acceptedby: acceptedby, oderStatus: status, orderId: orderId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    print(data)
                    self.getAlert(status:status)
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func getAlert(status: String) {
        var message = String()
        if status == String(OrderStatusType.InProgress.rawValue) {
            message = "You are Starting the new job. Drive carefully."
        } else {
            message = "Congratulations on completing the delivery. You can review the completed jobs in My completed jobs"
        }
        self.present(UIAlertController.alertWithTitle(title: "Job Updating", message: message, buttonTitle: "OK", handler: { action in self.updateLandingPage()}), animated: true)
    }
    
    func updateLandingPage() {
        self.navigationController!.popViewController(animated: true)
    }
}

// MARK:- ToolBar
extension UDMyJobDetailsViewController {
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
extension UDMyJobDetailsViewController: UITableViewDataSource, UITableViewDelegate {
    internal func numberOfSections(in tableView: UITableView) -> Int {
        return 3
    }
    
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 1
    }
    
    internal func tableView(_ tableView: UITableView, heightForHeaderInSection section: Int) -> CGFloat {
        return 5
    }
    
    internal func tableView(_ tableView: UITableView, heightForFooterInSection section: Int) -> CGFloat {
        return 0.0001
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        if indexPath.section == 0 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobDetailsCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            let customerName = myJobDict.object(forKey: "customername") as? String ?? ""
            let city = myJobDict.object(forKey: "city") as? String ?? ""
            let preferreddeliverytime = myJobDict.object(forKey: "preferreddeliverytime") as? Date ?? Date()
            let deliverDate = ConstantTools.sharedConstantTool.dayFormate(date: preferreddeliverytime)
            let deliverMonth = ConstantTools.sharedConstantTool.mothFormate(date: preferreddeliverytime)
            let time = ConstantTools.sharedConstantTool.timeFormate(date: preferreddeliverytime)
            let address = myJobDict.object(forKey: "address") as? String ?? ""
            let state = myJobDict.object(forKey: "state") as? String ?? ""
            let zip = myJobDict.object(forKey: "zip") as? String ?? ""
            let customerMobileNo = myJobDict.object(forKey: "phonenumber") as? String ?? ""
            cell.jobId.text = "Deliver to \(customerName) at\n\(address), \(city), \(state), \(zip)\n by \(deliverMonth) \(deliverDate) at \(time) \nCustomer Phone Number: \(customerMobileNo)"
            let orderId = myJobDict.object(forKey: "orderid") as? Int ?? 0
            let orderTitle = myJobDict.object(forKey: "ordertitle") as? String ?? ""
            cell.jobTitle.text = "\(orderId): \(orderTitle)"
            cell.jobDetails.text = "\(myJobDict.object(forKey: "orderdetails") as? String ?? "")"
            let orderStatus = myJobDict.object(forKey: "status") as? Int ?? 0
            cell.jobAcceptBtn.setTitle("Start the Job", for: .normal)
            cell.jobDismissBtn.setTitle("Complete the Job", for: .normal)
            if orderStatus == OrderStatusType.Accepted.rawValue {
                cell.jobAcceptBtn.backgroundColor = #colorLiteral(red: 0, green: 0.7254901961, blue: 0.8980392157, alpha: 1)
                cell.jobDismissBtn.backgroundColor = #colorLiteral(red: 0.6000000238, green: 0.6000000238, blue: 0.6000000238, alpha: 1)
                cell.jobAcceptBtn.isEnabled = true
                cell.jobDismissBtn.isEnabled = false
                cell.jobAcceptBtn.addTarget(self, action: #selector(tapToAcceptJobs(button:)), for: .touchUpInside)
            } else {
                cell.jobAcceptBtn.backgroundColor = #colorLiteral(red: 0.6000000238, green: 0.6000000238, blue: 0.6000000238, alpha: 1)
                cell.jobDismissBtn.backgroundColor = #colorLiteral(red: 0, green: 0.7254901961, blue: 0.8980392157, alpha: 1)
                cell.jobAcceptBtn.isEnabled = false
                cell.jobDismissBtn.isEnabled = true
                cell.jobDismissBtn.addTarget(self, action: #selector(tapToComplete(button:)), for: .touchUpInside)
            }
            return cell
        } else if indexPath.section == 1 {
            let cell = tableView.dequeueReusableCell(withIdentifier: "mapCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            let address = myJobDict.object(forKey: "address") as? String ?? ""
            let city = myJobDict.object(forKey: "city") as? String ?? ""
            let state = myJobDict.object(forKey: "state") as? String ?? ""
            let zip = myJobDict.object(forKey: "zip") as? String ?? ""
            let fullAddress = "\(address)\(city),\(state),\(zip)"
            ConstantTools.sharedConstantTool.getCoordinate(address: fullAddress, mapView: cell.mapView,customerName:fullAddress)
            cell.directionBtn.addTarget(self, action: #selector(tapToDirection(button:)), for: .touchUpInside)
            return cell
        } else {
            let cell = tableView.dequeueReusableCell(withIdentifier: "jobSectionCell", for: indexPath) as! UDJobDetailsTableViewCell
            cell.pulseAnimation = .none
            cell.packageCountLabel.text = "# of Packages: \(myJobDict.object(forKey: "numberofbags") as? Int ?? 0)"
            let perishable = myJobDict.object(forKey: "perishable") as? Bool ?? false
            let fragile = myJobDict.object(forKey: "fragile") as? Bool ?? false
            var isperishable = String()
            var isfragile = String()
            perishable == true ? (isperishable = "YES") : (isperishable = "NO")
            fragile == true ? (isfragile = "YES") : (isfragile = "NO")
            cell.fragileLabel.text = "Fragile: \(isfragile)"
            cell.perishablesLabel.text = "Pershables: \(isperishable)"
            cell.distanceLabel.text = "Weight: \(myJobDict.object(forKey: "totalweight") as? Int ?? 0) lbs"
            return cell
        }
    }
}
