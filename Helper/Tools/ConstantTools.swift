//
//  ConstantTools.swift
//  UDeli
//
//  Created by ARXT Labs on 6/21/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation
import Material
import CoreLocation
import MRProgress
import MapKit

class ConstantTools: NSObject {
    static let sharedConstantTool  = ConstantTools()
    var geocoder = CLGeocoder()
    var locationManager = CLLocationManager()
    var indicatorView = MRProgressOverlayView()
    
    //MARK:- MRProgressView
    func showsMRIndicatorView(_ view: UIView,text:String = "Loading") {
        indicatorView.removeFromSuperview()
        indicatorView = MRProgressOverlayView()
        indicatorView.mode = .indeterminateSmallDefault
        indicatorView.titleLabelText = text
        view.addSubview(indicatorView)
        indicatorView.show(true)
    }
    
    func hideMRIndicatorView() {
        indicatorView.dismiss(true)
    }
    
    // MARK: - Downloading Images
    func downloadImgFromUrl(url: URL, completion: @escaping (_ data: Data?, _  response: URLResponse?, _ error: Error?) -> Void) {
        URLSession.shared.dataTask(with: url) {
            (data, response, error) in
            if let httpResponse = response as? HTTPURLResponse {
                if httpResponse.statusCode != 200 {
                    return
                }
            }
            completion(data, response, error)
            }.resume()
    }
    
    // MARK: - TextField UI Colors
    func setTextFieldColor(textField:ErrorTextField) {
        textField.placeholderActiveColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        textField.placeholderLabel.textColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        textField.dividerActiveColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        textField.textColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        textField.placeholderNormalColor = #colorLiteral(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
    }
    
    // MARK: - Email Validation
    func isValidEmail(email:String) -> Bool {
        let emailRegEx = "^(?:(?:(?:(?: )*(?:(?:(?:\\t| )*\\r\\n)?(?:\\t| )+))+(?: )*)|(?: )+)?(?:(?:(?:[-A-Za-z0-9!#$%&’*+/=?^_'{|}~]+(?:\\.[-A-Za-z0-9!#$%&’*+/=?^_'{|}~]+)*)|(?:\"(?:(?:(?:(?: )*(?:(?:[!#-Z^-~]|\\[|\\])|(?:\\\\(?:\\t|[ -~]))))+(?: )*)|(?: )+)\"))(?:@)(?:(?:(?:[A-Za-z0-9](?:[-A-Za-z0-9]{0,61}[A-Za-z0-9])?)(?:\\.[A-Za-z0-9](?:[-A-Za-z0-9]{0,61}[A-Za-z0-9])?)*)|(?:\\[(?:(?:(?:(?:(?:[0-9]|(?:[1-9][0-9])|(?:1[0-9][0-9])|(?:2[0-4][0-9])|(?:25[0-5]))\\.){3}(?:[0-9]|(?:[1-9][0-9])|(?:1[0-9][0-9])|(?:2[0-4][0-9])|(?:25[0-5]))))|(?:(?:(?: )*[!-Z^-~])*(?: )*)|(?:[Vv][0-9A-Fa-f]+\\.[-A-Za-z0-9._~!$&'()*+,;=:]+))\\])))(?:(?:(?:(?: )*(?:(?:(?:\\t| )*\\r\\n)?(?:\\t| )+))+(?: )*)|(?: )+)?$"
        let emailTest = NSPredicate(format:"SELF MATCHES %@", emailRegEx)
        let result = emailTest.evaluate(with: email)
        return result
    }
    
    // MARK: - Mobile Validation
    func isValidMobileNumber(phoneNumber: String) -> Bool {
        let PHONE_REGEX = "^[0-9]{6,13}$"
        let phoneTest = NSPredicate(format: "SELF MATCHES %@", PHONE_REGEX)
        let result =  phoneTest.evaluate(with: phoneNumber)
        return result
    }
    
    //MARK:- Device Information
    func updateDeviceInformationWithDeviceToken(devicetoken:String) {
        userInfoDictionary = setDicitionaryValue()
        userInfoDictionary.setValue(devicetoken, forKey: "devicetoken")
        let data = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
        UserDefaults.standard.set(data, forKey: "userInfo")
    }
    
    func prepareDeviceInformation() {
        userInfoDictionary = setDicitionaryValue()
        let versionObject: AnyObject? = Bundle.main.infoDictionary!["CFBundleShortVersionString"] as AnyObject
        let version = versionObject as! String
        userInfoDictionary.setValue(UIDevice.current.identifierForVendor!.uuidString, forKey: "deviceid")
        userInfoDictionary.setValue(UIDevice.current.model, forKey: "model")
        userInfoDictionary.setValue(UIDevice.current.localizedModel, forKey: "localizedmodel")
        userInfoDictionary.setValue(UIDevice.current.name, forKey: "name")
        userInfoDictionary.setValue(UIDevice.current.systemVersion, forKey: "systemversion")
        userInfoDictionary.setValue(UIDevice.current.systemName, forKey: "systemname")
        userInfoDictionary.setValue(version, forKey: "appVersion")
        let data = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
        UserDefaults.standard.set(data, forKey: "userInfo")
    }
    
    func setDicitionaryValue() -> NSMutableDictionary {
        let data = UserDefaults.standard.object(forKey:"userInfo") as? Data ?? nil
        if data == nil {
            let Dictionary = NSMutableDictionary()
            return Dictionary
        }
        let Dictionary = NSKeyedUnarchiver.unarchiveObject(with: data!) as? NSMutableDictionary ?? [:]
        return Dictionary
    }
    
    func dateFormate(date:Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "MMM dd,yyyy"
        let dateFormate = dateFormatter.string(from: date)
        return dateFormate
    }
    
    func mothFormate(date:Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "MMM"
        let dateFormate = dateFormatter.string(from: date)
        return dateFormate
    }
    
    func dayFormate(date:Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "dd"
        let dateFormate = dateFormatter.string(from: date)
        return dateFormate
    }
    
    func timeFormate(date:Date) -> String {
        let timeFormate = DateFormatter()
        timeFormate.dateFormat = "h:mm a"
        let time = timeFormate.string(from: date)
        return time
    }
    
    //MARK:- MapView
    func getCoordinate(address: String,mapView:MKMapView,customerName:String) {
        let geocoder = CLGeocoder()
        geocoder.geocodeAddressString(address) { (placemarks, error) in
            if error == nil {
                if let placemark = placemarks?[0] {
                    let location = placemark.location!
                    let span = MKCoordinateSpan(latitudeDelta: 0.0075, longitudeDelta: 0.0075)
                    let region = MKCoordinateRegion(center: location.coordinate, span: span)
                    let annotation = MKPointAnnotation()
                    annotation.coordinate = location.coordinate
                    annotation.title = customerName
                    mapView.addAnnotation(annotation)
                    mapView.setRegion(region, animated: false)
                    return
                }
            }
        }
    }
}

//MARK:- CLLocationManagerDelegates
extension ConstantTools:CLLocationManagerDelegate {
    func getCurrentLocation() {
        isAuthorizedtoGetUserLocation()
    }
    
    func isAuthorizedtoGetUserLocation() {
        locationManager = CLLocationManager()
        locationManager.delegate = self
        locationManager.distanceFilter = kCLDistanceFilterNone
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
    }
    
    func handleLocationAuthorizationStatus(status: CLAuthorizationStatus) {
        switch status {
        case .notDetermined:
            locationManager.requestAlwaysAuthorization()
        case .authorizedAlways:
            locationManager.startMonitoringSignificantLocationChanges()
        case .authorizedWhenInUse:
            startUpdatingLocation()
        case .denied, .restricted:
            print("denied by user")
        }
        
    }
    
    func startUpdatingLocation() {
        locationManager.startUpdatingLocation()
    }
    
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        self.handleLocationAuthorizationStatus(status: status)
    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        locationManager.startUpdatingLocation()
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let location = CLLocation(latitude: Double((manager.location?.coordinate.latitude ?? 0.0)), longitude: Double((manager.location?.coordinate.longitude ?? 0.0)))
        geocoder.reverseGeocodeLocation(location) { (placemarks, ErrorType) -> Void in
            if ErrorType == nil && (placemarks?.count)! > 0 {
                self.locationManager.stopUpdatingLocation()
                let placemark = placemarks![0]
                let address = "\(placemark.thoroughfare ?? ""), \(placemark.locality ?? "")"
                //let locationAddress = placemarks![0].addressDictionary! as NSDictionary
                userInfoDictionary = self.setDicitionaryValue()
                userInfoDictionary.setValue(address, forKey: "location")
                userInfoDictionary.setValue("\(placemark.isoCountryCode ?? "")", forKey: "countryCode")
                userInfoDictionary.setValue("\(placemark.country ?? "")", forKey: "countryLocation")
                userInfoDictionary.setValue("\(placemark.postalCode ?? "")", forKey: "postalCodeLocation")
                userInfoDictionary.setValue("\(placemark.administrativeArea ?? "")", forKey: "stateLocation")
                userInfoDictionary.setValue("\(placemark.subLocality ?? "")", forKey: "cityLocation")
                userInfoDictionary.setValue(location.coordinate.longitude, forKey: "longitude")
                userInfoDictionary.setValue(location.coordinate.latitude, forKey: "latitude")
                let data = NSKeyedArchiver.archivedData(withRootObject: userInfoDictionary)
                UserDefaults.standard.set(data, forKey: "userInfo")
            }
        }
    }
}

//MARK:- UIAlertController
extension UIAlertController {
    static func alertWithTitle(title: String, message: String = "", cancelButtonTitle: String = "", buttonTitle: String="",handler: ((UIAlertAction) -> Void)? = nil,cancelHandler: ((UIAlertAction) -> Void)? = nil) -> UIAlertController {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        if cancelButtonTitle != "" {
            let cancel = UIAlertAction(title: cancelButtonTitle, style: .default, handler: cancelHandler)
            alertController.addAction(cancel)
        }
        if buttonTitle != "" {
            let action = UIAlertAction(title: buttonTitle, style: .default, handler: handler)
            alertController.addAction(action)
        }
        return alertController
    }
}

//MARK:- milesToKilometers
extension Double {
    func milesToKilometers() ->Double {
        let speedInMPH = self
        let speedInKPH = speedInMPH * 1.60934
        return speedInKPH as Double
    }
}

//MARK:- NSArray
extension NSArray {
    func countries() -> NSArray {
        let data = try? Data(contentsOf: URL(fileURLWithPath: Bundle.main.path(forResource: "countries", ofType: "json")!))
        do {
            let parsedObject = try JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions.allowFragments)
            return parsedObject as! NSArray
        }catch{
            print("not able to parse")
        }
        return []
    }
}

