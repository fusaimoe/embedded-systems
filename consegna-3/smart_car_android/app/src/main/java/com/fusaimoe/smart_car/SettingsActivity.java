package com.fusaimoe.smart_car;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.fusaimoe.smart_car.email.EmailManagement;

/**
 * Created by Giulia on 14/12/2016.
 */

public class SettingsActivity extends AppCompatActivity {

    private EditText email;
    private Button save;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_settings);

        email=(EditText)findViewById(R.id.emailTextBox);
        save=(Button)findViewById(R.id.save);
        email.setText(EmailManagement.getEmail());
        save.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                EmailManagement.setEmail(email.getText().toString());
            }
        });

    }

    /**
     * react to the user tapping the back/up icon in the action bar
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                this.onBackPressed();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
