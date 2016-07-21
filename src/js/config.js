module.exports = [
	{
    	"type": "heading",
		"defaultValue": "TOP Watchface Configuration"
	},
  	{
    	"type": "text",
    	"defaultValue": "Toggle the buttons to change settings."
  	},
	{
        "type": "toggle",
        "messageKey": "Lyrics",
        "label": "Enable Lyrics",
        "defaultValue": false
	},
	{
    	"type": "section",
    	"items": 
		[
			{
				"type": "heading",
				"defaultValue": "Colors"
			},
			{
				"type": "color",
				"messageKey": "TimeColor",
				"defaultValue": "0xFFFFFF",
				"label": "Time Color"
			},
			{
				"type": "color",
				"messageKey": "DateColor",
				"defaultValue": "0x000000",
				"label": "Date Color"
			},
			{
				"type": "color",
				"messageKey": "DayOfWeekColor",
				"defaultValue": "0x000000",
				"label": "Day of Week Color"
			},
			{
				"type": "color",
				"messageKey": "LyricsColor",
				"defaultValue": "0x000000",
				"label": "Lyrics Color"
			}
    	]
	},
  	{
    	"type": "submit",
    	"defaultValue": "Save Settings"
  	}	
];