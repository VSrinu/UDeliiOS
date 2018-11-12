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

 // MARK:- Twilio Key
public var twilioAPIKey = "ZP10uzqGKbOF6L9yix58eg7hznwhy91f"

 // MARK:- APPURL
public var msClientURL = MSClient(applicationURLString: "https://udelimobileapp.azurewebsites.net")

// MARK:- Table Name
let tCarrier = msClientURL.table(withName: "tcarrier")
let tmerchant = msClientURL.table(withName: "tmerchant")
let tOrders = msClientURL.table(withName: "tOrders")

