package com.fusaimoe.smart_car.email;

/**
 * Created by Giulia on 14/12/2016.
 */

public class EmailManagement {

    private static String email = "giulia.cecchetti96@gmail.com";

    public static void setEmail(String change){
        email=change;
    }

    public static String getEmail(){
        return email;
    }
}
