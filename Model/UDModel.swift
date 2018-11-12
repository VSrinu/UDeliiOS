//
//  UDModel.swift
//  UDeli
//
//  Created by ARXT Labs on 8/7/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct UDModel {
    // Get Merchant Details
    static func getMerchant(completion: @escaping (ConnectionResultAsArray) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let predicate = NSPredicate(format: "active = %@ AND usertype = %@", argumentArray: ["y", "m"])
                tmerchant.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        completion(.success(response))
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    // Update Merchant Id in tCarrier
    static func updateMerchantId(merchantId: Int, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["merchantid"] = merchantId
                    tCarrier.update(newItem as [NSObject: AnyObject], completion: { (result, error) -> Void in
                        if let err = error {
                            completion(.failure(err.localizedDescription))
                        } else if let item = result {
                            completion(.success(item as NSDictionary))
                        }
                    })
                }
            } else {
                completion(.failure(message))
            }
        }
    }
}
