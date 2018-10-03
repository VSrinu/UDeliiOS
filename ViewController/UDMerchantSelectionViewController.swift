//
//  UDMerchantSelectionViewController.swift
//  UDeli
//
//  Created by ARXT Labs on 8/7/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

class UDMerchantSelectionViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    var merchantArray = NSArray()
    var merchantSelection = NSDictionary()
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
        let data = UserDefaults.standard.object(forKey:"userInfo") as! Data
        userInfoDictionary = (NSKeyedUnarchiver.unarchiveObject(with: data) as! NSMutableDictionary?)!
        self.tableView.rowHeight = UITableView.automaticDimension
        self.tableView.estimatedRowHeight = 43
        self.tableView.tableFooterView = UIView()
        self.tableView.reloadData()
    }
    
    @IBAction func tapToUpdateMerchant(_ sender: Any) {
        let merchantId = merchantSelection.object(forKey: "merchantid") as? Int ?? 0
        let userTableId = userInfoDictionary.object(forKey: "id") as? String ?? ""
         ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your details")
        UDModel.updateMerchantId(merchantId: merchantId, userId: userTableId) { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    userInfoDictionary.setValuesForKeys(data as! [String : Any])
                    let userData = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                    UserDefaults.standard.set(userData, forKey: "userInfo")
                    self.tapToLandingPage()
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    func tapToLandingPage() {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDLandingViewController") as! UDLandingViewController
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}

// MARK:- UITableViewDataSource
extension UDMerchantSelectionViewController: UITableViewDataSource, UITableViewDelegate {
    internal func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return merchantArray.count
    }
    
    internal func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "tableViewCell", for: indexPath) as! UDTableViewCell
        let merchantDict:NSDictionary = merchantArray[indexPath.row] as! NSDictionary
        let merchantName = merchantDict.object(forKey: "name") as? String ?? ""
        cell.label.text = "Merchant Name : \(merchantName)"
        cell.accessoryType = .none
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .checkmark
        merchantSelection = merchantArray[indexPath.row] as! NSDictionary
    }
    
    internal func tableView(_ tableView: UITableView, didDeselectRowAt indexPath: IndexPath) {
        tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .none
    }
}

