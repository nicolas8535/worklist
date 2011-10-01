<?php
//  vim:ts=4:et

//  Copyright (c) 2011, LoveMachine Inc.
//  All Rights Reserved.
//  http://www.lovemachineinc.com
require_once("config.php");
require_once("class.session_handler.php");
include_once("check_new_user.php"); 
require_once("functions.php");
require_once 'models/DataObject.php';
require_once 'models/Users_Favorite.php';
require_once("send_email.php");

if ( !isset($_REQUEST['favorite_user_id']) ||
     !isset($_REQUEST['newVal']) ) {
    echo json_encode(array( 'error' => "Invalid parameters!"));
}
$userId = getSessionUserId();
if ($userId > 0) {
    initUserById($userId);
    $user = new User();
    $user->findUserById( $userId );

    $favorite_user_id = (int) $_REQUEST['favorite_user_id'];
    $newVal = (int) $_REQUEST['newVal'];
    $users_favorites  = new Users_Favorite();
    $res = $users_favorites->setMyFavoriteForUser($userId, $favorite_user_id, $newVal);
    if ($res == "") {
        // send chat if user has been marked a favorite
        $favorite_user = new User();
        $favorite_user->findUserById($favorite_user_id);
        if ($newVal == 1) {
                                
            $resetUrl = SECURE_SERVER_URL . 'worklist.php#userid=' . $favorite_user_id ;
            $resetUrl = '<a href="' . $resetUrl . '" title="Your profile">' . $resetUrl . '</a>';
            $data = array();
            $data['link'] = $resetUrl;
            $nick = $favorite_user->getNickname();
            if (! sendTemplateEmail($favorite_user->getUsername(), 'trusted', $data)) { 
                error_log("userinfo.php: send_email failed on favorite notification");
            }
        
            // get favourite count
            $count = $users_favorites->getUserFavoriteCount($favorite_user_id);
            if ($count > 0) {
                if ($count == 1) {
                    $message = "{$count} person";
                } else {
                    $message = "{$count} people";
                }
                $journal_message = "{$nick} is now trusted by {$message}!";
                //sending journal notification
                sendJournalNotification(stripslashes($journal_message));
            }
        }
        echo json_encode(array( 'return' => "Trusted saved."));
    } else {
        echo json_encode(array( 'error' => $res));
    }
} else {
    echo json_encode(array( 'error' => "You must be logged in!"));
}


