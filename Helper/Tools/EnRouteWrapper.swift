//
//  EnRouteWrapper.swift
//  oogioogi
//
//  Created by ARXT Labs on 10/03/18.
//  Copyright © 2018 ARXT Labs. All rights reserved.
//

import Foundation
import EnRouteApi

class EnRouteWrapper : NSObject, GlyListener {
    static let instance = EnRouteWrapper()
    
    private var _manager: GlyEnRouteManager?
    
    private override init() { // Prevent usage of default initializer
        super.init()
        createManager()
    }
    
    public func manager() -> GlyEnRouteManager? {
        return _manager
    }
    
    func eventsOccurred(_ source: GlySource!, listener: Int32, events: Int32, param1: GlyCommon!, param2: GlyCommon!) {
        if GlyEnRouteEvents.listener_ENROUTE_MANAGER() == listener {
            if GlyEnRouteEvents.enroute_MANAGER_STOPPED() == events {
                createManager()
            }
        }
    }
    
    private func createManager() {
        let active : Bool? = _manager?.isActive()
        _manager = GlyEnRouteFactory.createEnRouteManager()
        if active ?? true {
            _manager?.setActive(true);
        }
        _manager?.add(self)
    }
}
