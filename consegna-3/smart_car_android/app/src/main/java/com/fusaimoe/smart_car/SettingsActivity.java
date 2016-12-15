package com.fusaimoe.smart_car;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

/**
 * Created by Giulia on 14/12/2016.
 */

public class SettingsActivity extends AppCompatActivity {

    private EditText email;
    private Button save;
    private String receiverEmail;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Bundle extras = getIntent().getExtras();
        if(extras != null){
            receiverEmail = (String)extras.get("receiverEmail");
        }

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        setContentView(R.layout.activity_settings);

        email=(EditText)findViewById(R.id.emailTextBox);
        save=(Button)findViewById(R.id.save);

        /**Change the email**/
        save.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                receiverEmail= email.getText().toString();
            }
        });

        email.setText(receiverEmail);

    }

    /**
     * react to the user tapping the back/up icon in the action bar
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                /**Send the new Email to the MainActivity, if changed**/
                Intent mainActivityIntent = new Intent(this, MainActivity.class);
                if(receiverEmail!=null){
                    mainActivityIntent.putExtra("receiverEmail", receiverEmail);
                }
                this.startActivity(mainActivityIntent);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
}
