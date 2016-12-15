package com.fusaimoe.smart_car;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;

/**
 * Created by Giulia on 14/12/2016.
 */

public class SettingsActivity extends AppCompatActivity {

    private EditText email;
    private String receiverEmail;
    private Switch notificationSwitch;
    private boolean notifications;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Bundle extras = getIntent().getExtras();
        if(extras != null){
            receiverEmail = (String)extras.get(C.INTENT_EMAIL);
        }

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_settings);

        email = (EditText)findViewById(R.id.emailTextBox);
        notificationSwitch = (Switch)findViewById(R.id.emailSwitch);
        email.setText(receiverEmail);

    }

    /**
     * Add settings and maps action buttons to the top bar
     * @return
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu. This adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_settings, menu);
        return true;
    }

    /**
     * react to the user tapping the back/up icon in the action bar
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:

                // Send the new Email to the MainActivity, if changed
                Intent mainActivityIntent = new Intent(this, MainActivity.class);

                if(receiverEmail!=null){
                    mainActivityIntent.putExtra(C.INTENT_EMAIL, receiverEmail);
                }

                this.startActivity(mainActivityIntent);
                return true;
            case R.id.save:
                receiverEmail = email.getText().toString();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
