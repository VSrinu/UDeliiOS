//
//  Constants.swift
//  UDeli
//
//  Created by ARXT Labs on 6/21/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation
import MicrosoftAzureMobile

public var userInfoDictionary = NSDictionary()

 // MARK:- API Keys
public var twilioAPIKey = "ZP10uzqGKbOF6L9yix58eg7hznwhy91f"
public var googlePlaceAPIKey = "AIzaSyBOfkyB6Nrj1Pc5c0a18FglqZQstCDh1eQ"

 // MARK:- APPURL
public var msClientURL = MSClient(applicationURLString: "https://udelimobileapp.azurewebsites.net")

// MARK:- Table Name
let tCarrier = msClientURL.table(withName: "tcarrier")
let tmerchant = msClientURL.table(withName: "tmerchant")
let tOrders = msClientURL.table(withName: "tOrders")
let tOrderToCarriers = msClientURL.table(withName: "tOrderToCarriers")

