class CfgPatches
{
	class MT_Scripts
	{
		requiredAddons[] = { "DZ_Scripts" };
	};
};

class CfgAddons
{
    class PreloadAddons
    {
        class CookCrafter
        {
            list[]={};
        };
    };
};

class CfgMods
{
    class CookCrafter
    {
        name="CookCrafter";
        dir="CookCrafter";
        picture="";
        action="";
        author="Kares";
        overview = "";
		inputs = "CookCrafter/Scripts/Inputs.xml";
		type = "mod";
        defines[] = {};
		dependencies[] =
		{
			"Game", "World", "Mission"
		};

        class defs
		{
			class imageSets
			{
				files[]= {};
			};
			class widgetStyles
			{
				files[]= {};
			};

			class engineScriptModule 
			{ 
				files[] = { "CookCrafter/Scripts/1_Core"};
			};

			class gameScriptModule
			{
				files[] = { 
					"CookCrafter/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[] = { "CookCrafter/Scripts/4_World" };
			};

			class missionScriptModule 
			{
				files[] = { 
					"CookCrafter/Scripts/5_Mission"
				};
			};
		};
    };
};
