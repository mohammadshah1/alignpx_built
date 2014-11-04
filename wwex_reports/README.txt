Important Modules to be installed first
----------------------------------------
1) dropdown_checkboxes
-- Install the module in sites/all/modules/contrib/
-- Download and copy the ddcl directory in sites/all/Libraries/ (Please follow the steps given on https://www.drupal.org/project/dropdown_checkboxes) 
2) Downlaod and install "views_distinct" module in sites/all/modules/contrib/
3) Downlaod and install "views_php" module in sites/all/modules/contrib/
3a) Download and install  "views_aggregator" module in sites/all/modules/contrib
4) Download and install "colorbox" module in sites/all/modules/contrib/, Also download the colorbox jQuery 
    and place it in sites/all/Libraries/ (for configuration, please follow the steps given on module page(drupal site))
5) Downlaod and install "colorbox_node" module in sites/all/modules/contrib/ 
6) Downlaod and install "views_date_format_sql" (https://www.drupal.org/project/views_date_format_sql) module in sites/all/modules/contrib/ 
7) Install the attached custom module (wwex_reports) in sites/all/modules/custom/
8) After installation is complete, Please clear your site cache by going to admin/config/development/performance
---------------------------------------------------------------------------------------------------------
Now, You will have a new menu item "Load by count date", On the left navigation under the "Historical Lane Data" 

To have parent level of the "Load by count date" link follow the steps below:
-------------------------------------------------------------------------------
1) Downlaod and install "special_menu_items" module in sites/all/modules/contrib/
----- Create new Menu Item in "Main menu"
----- Type <nolink> (with tags) in path text field on form. 
----- Make this menu as a parent item of "Load by Count date" menu link 
----- Save
2) Clear site cache 