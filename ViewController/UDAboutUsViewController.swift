//
//  UDAboutUsViewController.swift
//  oogioogi
//
//  Created by ARXT Labs on 11/27/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import UIKit
import Material
import WebKit

class UDAboutUsViewController: UIViewController {
    @IBOutlet weak var toolBar: Toolbar!
    @IBOutlet weak var webView: WKWebView!
    fileprivate var backButton: IconButton!
    override func viewDidLoad() {
        super.viewDidLoad()
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
        webView.navigationDelegate = self
        let url = NSURL (string:"https://oogioogi-63.webself.net/about")
        let requestObj = URLRequest(url: url! as URL)
        self.webView.load(requestObj)
    }
}

// MARK:- ToolBar
extension UDAboutUsViewController {
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

extension UDAboutUsViewController:WKNavigationDelegate {
    internal func webView(_ webView: WKWebView, didStartProvisionalNavigation navigation: WKNavigation!) {
        ConstantTools.sharedConstantTool.showsMRIndicatorView(self.view)
    }
    
    internal func webView(_ webView: WKWebView, didFinish navigation: WKNavigation!) {
        ConstantTools.sharedConstantTool.hideMRIndicatorView()
    }
}
