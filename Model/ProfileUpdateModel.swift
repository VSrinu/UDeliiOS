//
//  prifileUpdateModel.swift
//  oogioogi
//
//  Created by ARXT Labs on 8/7/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation

struct ProfileUpdateModel {
    //Update Status
    static func updateStatus(profileStatus: Int, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["profilestatus"] = profileStatus
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
    
    //Update Profile
    static func updateprofile(fName: String, lName: String, emailId: String, address: String, city: String, state: String, zipcode: String, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["firstname"] = fName
                    newItem["lastname"] = lName
                    newItem["emailid"] = emailId
                    newItem["address"] = address
                    newItem["city"] = city
                    newItem["state"] = state
                    newItem["zip"] = zipcode
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
    
    //Update Profile Image
    static func updateprofileImage(image: String, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["profileimage"] = image
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
    
    //Update Notification Type
    static func updateNotificationType(notificationType: Int, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["notificationtype"] = notificationType
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
    
    //Update Distance From Home
    static func updateDistanceFromHome(distancefromhome: Int, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["distancefromhome"] = distancefromhome
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
    
    //Update Distance From Store
    static func updateDistanceFromStore(distancefromstore: Int, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["distancefromstore"] = distancefromstore
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
    
    //Get User Details
    static func getUserDetails(userId: String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let predicate = NSPredicate(format: "id = %@", argumentArray: [userId])
                tCarrier.read(with: predicate) { (result, error) in
                    if let err = error {
                        completion(.failure(err.localizedDescription))
                    } else if let items = result?.items {
                        let response = items as NSArray
                        if response.count == 0 {
                            completion(.failure("Unable to get User Details"))
                        } else {
                            completion(.success(response.firstObject as! NSDictionary))
                        }
                    }
                }
            } else {
                completion(.failure(message))
            }
        }
    }
    
    //Update Device Tken
    static func updateDeviceToken(devicetoken: String, userId:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["devicetoken"] = devicetoken
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
    
    //Update Status
    static func updateUserLocation(userId:String, latitude:String, longitude:String, completion: @escaping (ConnectionResultAsDictionary) -> ()) {
        Internet.isAvailable { (status, message) in
            if status {
                let itemDict: NSDictionary = ["id": userId]
                if let newItem = itemDict.mutableCopy() as? NSMutableDictionary {
                    newItem["live_latitude"] = latitude
                    newItem["live_longitude"] = longitude
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
