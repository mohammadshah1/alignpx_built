==========================================
INTRODUCTION
==========================================

This file explains how to Add left menu (Reports) and installing report modules (wwex_reports, wwex_revenue_report, wwex_sales_rep_report, 
wwex_shipments_by_date, wwex_shipments_detail_report, wwex_tier_report,wwex_report_charts) along with few drupal contributed modules and custom dependent module (wwex_views_uid_filter).

	Note: (Adding a "Reports" menu in main-menu), Make sure that report menu is created first under main-menu (steps defined below in "Configuration" section). Also, Please make sure that "wwex_views_uid_filter" module is install first, 
	because this module adds our custom views filter field (Content: Author UID (select list)) into view filters section.

==========================================
REQUIREMENTS
==========================================

	
	
1)  Download the "sexy_exposed" module, to enable checkbox selection on search form select boxes.
		Module download link : https://www.drupal.org/project/sexy_exposed
		Extract the file and upload it to site.Make sure that the path of module is (/sites/all/modules/contrib/) and all required js files are copied to sites/all/libraries/ folder.
		Important Note: Once this module is installed successfully, You will have to (Edit) the view where you want checkboxes facility in exposed form filter fields, 
		and check the option "make it sexy" in field configuration. 
		This must be done once the report modules are installed (Please refer to "REPORT MODULES INSTALLATION" section at the bottom of this file) 
2)  Download visualization module and install it into sites/all/modules, Also download all its highcharts js files and extract into sites/all/libraries/
		( Note: In visualization configuration you must select highcharts library and save )	


===============================================
Theme configuration for CSS
===============================================
Upload table.css file to theme folder make sure the path is like(/sites/all/themes/e3_zen/css/table.css).
Upload charts.css file to theme folder make sure the path is like(/sites/all/themes/e3_zen/css/charts.css).
Upload commen.css file to theme folder make sure the path is like(/sites/all/themes/e3_zen/css/common.css).
Now open template.php following the path (/sites/all/themes/e3_zen/template.php).
Place this line of code "drupal_add_css(E3_ZEN . '/css/table.css');" (Just below this comment -> // Add site CSS) inside this function "function e3_zen_preprocess_html()".
Place this line of code "drupal_add_css(E3_ZEN . '/css/charts.css');" (Just below this comment -> // Add site CSS) inside this function "function e3_zen_preprocess_html()".
Place this line of code "drupal_add_css(E3_ZEN . '/css/common.css');" (Just below this comment -> // Add site CSS) inside this function "function e3_zen_preprocess_html()".

Save the file.


####################################################
REPORT MODULES INSTALLATION
==================================================================================================================
NOTE: After Installing All Report Modules mentioned in introduction section above,(Some necessary steps to do after enabling report modules)
==================================================================================================================

==========================================
INSTALLATION
==========================================
First download contributed module called Special menu items from (https://www.drupal.org/project/special_menu_items) path.
Extract and upload it to directory,make sure path is /sites/all/modules/contrib/
Go to Path /admin/modules and enable Special menu item module.
Click on Save configuration.
==========================================
CONFIGURATION
==========================================

Creating Report menu link:


Step no 1: Go to /admin/structure/menu 
Step no 2: Click on add link in front of Main menu, Make sur path is /admin/structure/menu/manage/main-menu/add
Step no 3: Add title Reports in Menu link title and add <nolink> in Path.check Enabled and check Show as expanded checkbox.
Step no 4: Make sure that <Main Menu> is selected in dropdown list in Parent link if not select it from dropdown list.
Step no 5: Make sure that -43 is selected in dropdown list in Weight if not select it from dropdown list.
Step no 6: Make sure that None (i.e same window) is selected in dropdown list in Target if not select it from dropdown list.
Step no 7: Click on Save button.


Creating Report List links:

Step no 1: Go to /admin/structure/menu 
Step no 2: Click on list link in front of Main menu, Make sure path is /admin/structure/menu/manage/main-menu
Step no 3: Drag and drop following list of links below Report link.i.e
	
	Tier Report
	Shipment By Dates 
	Shipment Detail	
	Sale Rep Report	
	Load by Count Date 	
	Time Shipper	
	Market Performance Report
	Revenue Report

================================	
Addational 
================================

Edit Every report view by clicking the gear on right top of view (When you have admin Rights a gear will appear hovering mouse on it an edit view option appears click on that).
For example(/admin/structure/views/view/shipment_detail_report/edit/shipment_detail_report?destination=shipment-detail-report).
Now open filter fields one by one in filter criterion section, 
A Configure filter criterion popup will open. first of all please make sure that "This display/attachment" is selected in popup window then follow below steps.
Scroll downward and check the box "allow multiple selection" and "Make it sexy" options and click on Apply.
Now open another field in the same filters section and follow the same method.

(Note: these are only for multi-select fields and non-date fields, do not do this for any date filter fields).





