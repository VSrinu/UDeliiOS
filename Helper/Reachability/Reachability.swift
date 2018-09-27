//
//  UDCustomViewControllerDelegates.swift
//  UDeli
//
//  Created by ARXT Labs on 6/28/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//


import Foundation
import Reachability

struct Internet {
    static func isAvailable(completion:@escaping(_ status:Bool,_ message:String)->()) {
        let networkCheck = Reachability()
        networkCheck?.whenReachable = { reachability in
            DispatchQueue.main.async {
                reachability.connection == .wifi ? completion(true,"WiFi") : completion(true,"Mobile Network")
            }
        }
        networkCheck?.whenUnreachable = { reachability in
            DispatchQueue.main.async {
                completion(false,"Network connectivity not available")
            }
        }
        do {
            try networkCheck?.startNotifier()
        } catch {
            print("From: REACHABILITY \n Unable to Start Notifier")
        }
    }
}
