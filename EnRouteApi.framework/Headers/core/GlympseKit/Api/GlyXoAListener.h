//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GlyXoAListener< NSObject >

- (BOOL)shouldMonitorTicket:(GlyTicket*)ticket;

@end