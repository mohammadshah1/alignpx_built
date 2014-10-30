==========================================
INTRODUCTION
==========================================

This file explains how to Add left menu (Reports) and installing report modules (wwex_reports, wwex_revenue_report, wwex_sales_rep_report, 
wwex_shipments_by_date, wwex_shipments_detail_report, wwex_tier_report,wwex_report_charts) along with few drupal contributed modules and custom dependent module (wwex_views_uid_filter).

	Note: (Adding a (Reports) menu), Make sure that report menu is created first.Check report menu in list on the path(i.e /admin/structure/menu/)
				Also, Please make sure that "wwex_views_uid_filter" module is install first, because this module adds our custom views filter field (Content: Author UID (select list)) into view filters section.

==========================================
REQUIREMENTS
==========================================

1) 	Download the TB Mega Menu (7.x-1.x-dev) from the below link.
		https://www.drupal.org/project/tb_megamenu
		Extract the file and upload it to site.Make sure that the path of module is (/sites/all/modules/contrib/tb_megamenu).
2)  Download the "sexy_exposed" module, to enable checkbox selection on search form select boxes.
		Module download link : https://www.drupal.org/project/sexy_exposed
		Extract the file and upload it to site.Make sure that the path of module is (/sites/all/modules/contrib/tb_megamenu).
		Important Note: Once this module is installed successfully, You will have to (Edit) the view where you want checkboxes facility in exposed form filter fields, 
		and check the option "make it sexy" in field configuration. 
		This must be done once the report modules are installed (Please refer to "REPORT MODULES INSTALLATION" section at the bottom of this file) 

==========================================
INSTALLATION
==========================================

Go to modules links,search for TB mega menu and just enable it by clicking checkbox on and save configuration.(Make sure you have administrative rights to install it).
i.e(/admin/modules).

==========================================
CONFIGURATION
==========================================

Now create a menu link with name (Shipment Reports Menu) by following below steps.
Go to structure->menu
ie (/admin/structure/menu/add)
Click on Add menu,Enter the name of your menu (Shipment Reports Menu) and Click save.
Also, create (Reports) link in main-menu (/admin/structure/menu/manage/main-menu/add).

Now for TB menu go to structure TB mega menu ie (/admin/structure/tb-megamenu) Make sure your menu "Shipment Reports Menu" appear in list.
Click on "Config" link of main menu, there you will see all main-menu links/tabs. 
Click on "Reports" tab, Setting for the this tab will be visible at the top.
On first option "Submenu" change to "yes", 
Now a textfield type will become visible under "Reports" tab. By clicking on it, and then 
On the top "Tab Configuration" section, In "Blocks" drop down select block "Shipment Reports Menu".
Goto Blocks section here /admin/structure/block, and enable "TB Mega Menu: Main menu" block by selection "navigation bar" region and click on save button.
Clear site's cache.
Click save, and a Reports menu with sub menus will be created on left side navigation bar.

===============================================
Theme configuration for CSS
===============================================
Upload table.css file to theme folder make sure the path is like(/sites/all/themes/e3_zen/css/table.css).
Upload charts.css file to theme folder make sure the path is like(/sites/all/themes/e3_zen/css/charts.css).
Now open template.php following the path (/sites/all/themes/e3_zen/template.php).
Place this line of code "drupal_add_css(E3_ZEN . '/css/table.css');" (Just below this comment -> // Add site CSS) inside this function "function e3_zen_preprocess_html()".
Place this line of code "drupal_add_css(E3_ZEN . '/css/charts.css');" (Just below this comment -> // Add site CSS) inside this function "function e3_zen_preprocess_html()".

Save the file.

Now open the header.inc file following the path i.e(/sites/all/themes/e3_zen/page_layouts/includes/header.inc) and replace the most last line
i.e 
#############
print render($page['navigation']);
#############

replace it by the following piece of code.
#######
unset($page['navigation']['system_main-menu']);
print render($page['navigation']);

######### 
now save the file.

####################################################
REPORT MODULES INSTALLATION
==================================================================================================================
NOTE: After Installing All Report Modules mentioned in introduction section above,(Some necessary steps to do after enabling report modules)
==================================================================================================================
Edit Every report view by clicking the gear on right top of view (When you have admin Rights a gear will appear hovering mouse on it an edit view option appears click on that).
For example(/admin/structure/views/view/shipment_detail_report/edit/shipment_detail_report?destination=shipment-detail-report).
Now open filter fields one by one in filter criterion section, 
A Configure filter criterion popup will open. first of all please make sure that "This display/attachment" is selected in popup window then follow below steps.
Scroll downward and check the box "allow multiple selection" and "Make it sexy" options and click on Apply.
Now open another field in the same filters section and follow the same method.

(Note: these are only for multiselcet fields and non-date fields, do not do this for any date filter fields).


