# Plant-Buddy
This code was created to use the Soil Moisture Sensor by SparkFun and an Arduino Mkr 1000 wifi to send data to a google doc and ios reminders using an api. 
This is the full tutorial for this project, including hardware, https://medium.com/p/409e4befc614#38d8-86c16af9595e. 

Tutorial: 

Our information is going to be sent and recorded on google sheets. Open a new Google Sheet using your Gmail. Name the Google Sheet whatever you want and then get ready to save a long string of characters. So where the URL of the Google Sheet is you’re going to see a /d/ followed by a bunch of random letters and numbers, and then /edit. This is called the URL Key to your spreadsheet. Copy and paste that somewhere for use later. Now we’re going to add some code to this sheet. To do so we need to open Google Script, also known as Gscript. Extensions > Apps Script. Once there, name the Gscript and delete the starter code on there. Put the GScript code privided in there, make sure to place your URL Key next to var Id = .  Now that we have the code in place, we have to deploy this. To do so, click deploy on the top right corner. Deploy > New Deployment, from the pop-up tab select the gear icon in the top left corner next to where it says “Select Type”. Gear > Web App. Put any sort of description, for the second box where it says “execute as”, make sure it’s set to you with your email. For the third box where it says “who has access”, set it to anyone even anonymous. From here, click deploy on the bottom right corner. Make sure to save the Web App URL that just popped up. Copy and paste it somewhere for use later.

We need something to send the information from the sensor to the google sheet, this would be called an API middleman. We’re going to use PushingBox.
Create a free account with your Gmail. Click “My Services” > “Add a Service” > “CustomURl”, “Select This Service”. Fill in the name of the configuration with anything you want. In the second box, paste the Web App URL we saved from the gscript. In the third box, choose the GET option. Now we have to program this service. To do so, click on “My Scenarios” from the bar on the top. Name it anything you want then click the add button. Click the “Add an Action” button at the bottom > click the “Add an Action with this Service” for the service we just set. > copy and paste the code below into the box that just popped up. We are using the GET code provided for this. Copy and paste the DeviceID somewhere for later use.

We’re going to test what we’ve done so far so that we can make sure we haven’t missed anything before we move on. To do so we are going to manually input data into the sheet. Copy and paste this into your browser, but with your DeviceID that we just saved from PushingBox.

http://api.pushingbox.com/pushingbox?devid=(YOUR-DEVID-HERE)&moistureHum=33

Check your google sheet for the update to make sure everything is working. If not, double-check everything else we’ve done in this part so far for errors.

If you haven’t already, download the Arduino app. We also need to download a library, this is a package that contains information on how to use different premade codes, for example, for our Arduinos wifi module.
https://github.com/arduino-libraries/WiFi101
Open Arduino, it should open a blue-rimmed tab with some basic code. We need to first choose the board and port that we are going to work with. To choose the board, plug your Arduino into your device with the micro USB wire, any port works but I used the left USB one on my mac. Then, click over tools on the top left corner > board > boards manager > Arduino SAMD Boards > install. This downloads information for a bunch of boards, including the one we need to use. After you download it just close the manager and backtrack, so instead of clicking boards manager again, you hover over the Arduino SAMD Boards > Arduino MKR 1000. 

Now we have to code the Arduino. Input the code provided.  We have to customize some parts of the code. Plug them in the code where they're written.

Your SSID (your WiFi name)
Your WiFi password
Your DeviceID from Pushingbox

To make the code run first click the checkmark button on the top left to verify that it works, then while the Arduino is still plugged in click the Upload button. It would ask you to save the file so just save it in any name and anywhere you want.

Now to make everything come together go-to tools > serial monitor. Keep this tab open and running and you should see it updating within here, as long as it updates on the monitor it should also be updating to the google sheet!

We’re at the last and easiest step!

Sign up for IFTTT. Click “create” and click “add” for the first part of the applet. Search for google sheets and then choose the option for “new row added to spreadsheet”. Link your email to it, and put the URL of the google sheet in where required. Fill up the base connection parts shown to you. For the “then that” part click “add” and search for “ios reminders” and choose that option. Set up the first part like this, and you can either fill out the rest of the options as you want or just let it be. Download the mobile app and allow changes.
