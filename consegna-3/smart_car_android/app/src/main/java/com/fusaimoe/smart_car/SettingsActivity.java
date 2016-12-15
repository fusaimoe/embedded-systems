package com.fusaimoe.smart_car;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.Toast;

/**
 * Created by Giulia on 14/12/2016.
 */

public class SettingsActivity extends AppCompatActivity {

    private EditText email;
    private Switch notifications;
    private SharedPreferences preferences;

    /**
     * todo
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        preferences = this.getPreferences(Context.MODE_PRIVATE);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_settings);

        email = (EditText)findViewById(R.id.emailTextBox);
        notifications = (Switch)findViewById(R.id.emailSwitch);

        // Set both values either to their saved values or to default values
        email.setText(preferences.getString(getString(R.string.userEmailPreference), getString(R.string.emailDefaultAddress)));
        notifications.setChecked(preferences.getBoolean(getString(R.string.userNotificationsPreference), false));
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
     * React to the user tapping the back icon in the action bar
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:

                Intent mainActivityIntent = new Intent(this, MainActivity.class);
                this.startActivity(mainActivityIntent);

                return true;
            case R.id.save:

                SharedPreferences.Editor editor = preferences.edit();

                editor.putBoolean(getString(R.string.userNotificationsPreference), notifications.isChecked());

                if(!email.getText().toString().equals("") || !email.getText().toString().contains("@") || !email.getText().toString().contains(".")){

                    editor.putString(getString(R.string.userEmailPreference), email.getText().toString());
                    editor.commit();

                    return true;

                } else {

                    Toast.makeText(getApplicationContext(), R.string.emailNotValid, Toast.LENGTH_SHORT).show();

                }
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
