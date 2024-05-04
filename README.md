# ESP32 data on Google Sheet

This project is a simple example of how to send data from ESP32 to Google Spread Sheets using Google Apps Script.

## Google Sheets

Create a new Google Spread Sheet and add the following headers in the first row:

```
Timestamp | Temperature | Humidity | Heat Index | RawSGP40
```

Note down the Google Spread Sheet ID from its URL and replace it with `<YOUR_GOOGLE_SPREAD_SHEET_ID>` in `script.js`

For Example: Sample Google SpreadSheet URL
https://docs.google.com/spreadsheets/d/1hhUCOQtAi2QdW7ID2sm5YaQ1-0a46YPrn2F1G_SYycM/edit#gid=186001220

In this case, Google Spread Sheet ID is "1hhUCOQtAi2QdW7ID2sm5YaQ1-0a46YPrn2F1G_SYycM". Following this format https://docs.google.com/spreadsheets/d/GOOGLE_SPREAD_SHEET_ID/edit#gid=0

## Google Apps Script

- Go to [Google Apps Script](https://script.google.com/u/1/home/start) and start a new project.
- Replace the boiler plate function with the code present in `script.js` (make sure to include your Google Sheet ID following the above instructions).
- Now its time to deploy this project so this script can receive data from Esp32 and send to Google Sheet.
- Go to Deploy>New Deployment>Select Type>Web App
- Give some description for the project (optional)
- Make sure to change the access to `Anyone` otherwise data transfer wont work
- Press `Deploy` and wait for sometime and then a pop up will appear
- Copy the Web app URL and replace it with `YOUR_GOOGLE_APPS_SCRIPT_URL` in `esp32.cpp`

  (If you lose this Web app URL, you can always go to Deploy>Manage Deployments and get it back)

#### Wanna change the Google Sheet to send the data to?

- Get the new Google Sheet ID just like before
- Update the ID present in your Google Apps Script's Project
- Now go to Deploy>Manage Deployments and press the `✏️` (Edit) icon
- Without changing anything just press `Deploy` (without doing this, new changes wont take effect and data will still go to the old Google Sheet)

#### Note

- Make sure to use the same Google Account for Google Sheet and Google Apps Script
