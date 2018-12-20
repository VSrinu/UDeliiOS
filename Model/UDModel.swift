    //
    //  UDModel.swift
    //  oogioogi
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
        
        // Add Merchant Id in tCarrierToMerchants
        static func addMerchantsOfCarrier(carrierId: Int, merchantId: Int, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
            Internet.isAvailable { (status, message) in
                if status {
                    // Insert details
                    let itemToInsert = ["carrierid": carrierId, "merchantid": merchantId] as [String : Any]
                    tCarrierToMerchants.insert(itemToInsert) { (result, error) in
                        if let err = error {
                            completion(.failure(err.localizedDescription))
                        } else if let item = result {
                            let response = item as NSDictionary
                            completion(.success(response))
                        }
                    }
                } else {
                    completion(.failure(message))
                }
            }
        }
        
    }
