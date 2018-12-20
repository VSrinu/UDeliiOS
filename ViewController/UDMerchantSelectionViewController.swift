//
//  UDMerchantSelectionViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 8/7/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

class UDMerchantSelectionViewController: UIViewController {
    @IBOutlet weak var tableView: UITableView!
    var merchantArray = NSArray()
    var merchantSelectionArray = NSMutableArray()
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
        for merchantDetails in merchantSelectionArray {
            let carrierId = (merchantDetails as AnyObject).object(forKey: "merchantid") as? Int ?? 0
            let userId = userInfoDictionary.object(forKey: "carrierid") as? Int ?? 0
            ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view,text: "updating your details")
            UDModel.addMerchantsOfCarrier(carrierId: carrierId, merchantId: userId) { connectionResult in
                DispatchQueue.main.async(execute: {() -> Void in
                    ConstantTools.sharedConstantTool.hideMRIndicatorView()
                    switch connectionResult {
                    case .success(let data):
                        print(data)
                    case .failure(let error):
                        self.view.makeToast(error, position: .top)
                        return
                    }
                })
            }
        }
        self.tapToLandingPage()
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
        let cell = tableView.dequeueReusableCell(withIdentifier: "tableViewCell", for: indexPath) as! UDMerchantSelectionTableViewCell
        let merchantDict:NSDictionary = merchantArray[indexPath.row] as! NSDictionary
        let merchantName = merchantDict.object(forKey: "name") as? String ?? ""
        cell.logo.layer.borderWidth = 1
        cell.logo.layer.masksToBounds = false
        cell.logo.layer.borderColor = UIColor.black.cgColor
        cell.logo.layer.cornerRadius = cell.logo.frame.height/2
        cell.logo.clipsToBounds = true
        cell.titleLabel.text = "\(merchantName)"
        let address = merchantDict.object(forKey: "address") as? String ?? ""
        let city = merchantDict.object(forKey: "city") as? String ?? ""
        let country = merchantDict.object(forKey: "country") as? String ?? ""
        let zip = merchantDict.object(forKey: "zip") as? String ?? ""
        cell.detailsLabel.text = "\(address), \(city), \(country)-\(zip)"
        cell.accessoryType = .none
        if cell.isSelected {
            cell.isSelected = false
            if cell.accessoryType == UITableViewCell.AccessoryType.none {
                cell.accessoryType = UITableViewCell.AccessoryType.checkmark
            } else {
                cell.accessoryType = UITableViewCell.AccessoryType.none
            }
        }
        return cell
    }
    
    internal func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        let cell = tableView.cellForRow(at: indexPath)
        if cell!.isSelected {
            cell!.isSelected = false
            if cell!.accessoryType == UITableViewCell.AccessoryType.none {
                cell!.accessoryType = UITableViewCell.AccessoryType.checkmark
                merchantSelectionArray.add(merchantArray[indexPath.row] as! NSDictionary)
            } else {
                cell!.accessoryType = UITableViewCell.AccessoryType.none
                merchantSelectionArray.remove(merchantArray[indexPath.row] as! NSDictionary)
            }
        }
        //tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .checkmark
        //merchantSelection = merchantArray[indexPath.row] as! NSDictionary
    }
    
    internal func tableView(_ tableView: UITableView, didDeselectRowAt indexPath: IndexPath) {
        //tableView.cellForRow(at: indexPath as IndexPath)?.accessoryType = .none
    }
}

