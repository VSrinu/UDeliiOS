//------------------------------------------------------------------------------
//
// Copyright (c) 2016 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ICARDTYPE_H__GLYMPSE__
#define ICARDTYPE_H__GLYMPSE__

namespace Glympse
{

/**
 * Exposes basic properties for types of cards.
 *
 * Host application does not create or modify card type objects directly. Instead it uses methods
 * exposed by ICardManager.
 */
/*O*public**/ struct ICardType : public virtual ICommon
{
    /**
     * @return Gets card type ID.
     */ 
    public: virtual GString getId() = 0;

    /**
     * @return Gets card type name.
     */
    public: virtual GString getName() = 0;

    /**
     * @return Gets card type category.
     */
    public: virtual GString getCategory() = 0;

    /**
     * @return Gets card type description.
     */
    public: virtual GString getDescription() = 0;
    
    /**
     * Gets the list of notifications supported by cards of current type.
     *
     * Each notification primitive has the following properties:
     * - type: string
     * - presenter: string
     *
     * The following notification types are supported:
     * - member_added
     * - member_removed
     * - member_started_sharing
     * - member_started_requesting
     * - invite_added
     * - invite_removed
     *
     * @note Some notification types may be omitted from the list leaving host application in charge of
     * picking the most appropriate mechanism for presenting those.
     *
     * The following presenter options are avaialble:
     * - app - application is supposed to render local notification;
     * - sdk - SDK does what it takes to notify the user;
     * - os - user is notified via remote notification.
     *
     * @return The list of card type notifications.
     */
    public: virtual GArray<GPrimitive>::ptr getNotifications() = 0;
    
    /**
     * @param type Card notification type.
     * @return Card notification type of NULL if it is not found.
     */
    public: virtual GPrimitive findNotificationByType(const GString& type) = 0;
};

/*C*/typedef O< ICardType > GCardType;/**/

}

#endif // !ICARDTYPE_H__GLYMPSE__
