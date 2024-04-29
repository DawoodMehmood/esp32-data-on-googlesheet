function doPost(e) {
  // Open the Google Sheet by ID and get a reference to its API service.
  // Replace <Google SpreadSheet ID> with the ID of your Google SpreadSheet.
  // {How to get the Google SpreadSheet ID from the URL: https://developers.google.com/sheets/api/guides/concepts#spreadsheet_id}
  // E.g. Sample Google SpreadSheet URL
  //https://docs.google.com/spreadsheets/d/1hhUCOQtAi2QdW7ID2sm5YaQ1-0a46YPrn2F1G_SYycM/edit#gid=186001220
  // The Google SpreadSheet ID is "1hhUCOQtAi2QdW7ID2sm5YaQ1-0a46YPrn2F1G_SYycM" in this case
  // following this format https://docs.google.com/spreadsheets/d/spreadsheetId/edit#gid=0
  var sheet = SpreadsheetApp.openById(
    "<Google SpreadSheet ID>"
  ).getActiveSheet();
  // Parse the JSON data
  var data = JSON.parse(e.postData.contents);
  // append data to the Google Sheet here
  // Date | Temperature | Humidity | Heat Index | Raw SGP40
  sheet.appendRow([
    new Date(),
    data.temperature,
    data.humidity,
    data.heat_index,
    data.raw_sgp40,
  ]);
  // Return success
  return ContentService.createTextOutput(
    JSON.stringify({ result: "success" })
  ).setMimeType(ContentService.MimeType.JSON);
}
