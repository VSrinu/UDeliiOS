//
//  UDWelcomeViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 7/30/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit

class UDWelcomeViewController: UIViewController {
    @IBOutlet weak var selectMerchantView: UIView!
    @IBOutlet weak var detailsLabel: UILabel!
    var merchantArray = NSArray()
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
        detailsLabel.text = "Thank you for registering with OogiOogi. We have notified the merchant and your application is under review. Once approved, we will update you by Email & SMS. In the meantime, please specify your driving distance as a final step."
        getMerchantDetails()
    }
    
    func getMerchantDetails() {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
        UDModel.getMerchant() { connectionResult in
            DispatchQueue.main.async(execute: {() -> Void in
                ConstantTools.sharedConstantTool.hideMRIndicatorView()
                switch connectionResult {
                case .success(let data):
                    self.merchantArray = data
                case .failure(let error):
                    self.view.makeToast(error, position: .top)
                }
            })
        }
    }
    
    // MARK:- Target Action Buttons
    @IBAction func tapToSubmitMerchant(_ sender: Any) {
        let storyboard = UIStoryboard(name: "iPhoneStoryboard", bundle: nil)
        let viewController = storyboard.instantiateViewController(withIdentifier: "UDMerchantSelectionViewController") as! UDMerchantSelectionViewController
        viewController.merchantArray = merchantArray
        self.navigationController?.pushViewController(viewController, animated: true)
    }
}
