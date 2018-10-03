//------------------------------------------------------------------------------
//
//  Copyright (c) 2016 Glympse Inc. All rights reserved.
//
//------------------------------------------------------------------------------

@interface GlyEtaTrigger : GlyTrigger

- (GlyTicket*)getEtaTicket;

- (long long int)getThreshold;

- (int)getTransition;

@end