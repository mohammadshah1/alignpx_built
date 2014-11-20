(function($) {

Drupal.behaviors.wwtx_charts = {
  attach: function(context) {  
    $.each($(".wwtx-charts-chart-highcharts", context).not(".wwtx-charts-processed"), function(idx, value) {
      var chart_id = $(value).attr("id");
      var chart = Drupal.settings.wwtx_charts[chart_id];
	  console.log(chart_id);
      $(value).addClass("wwtx-charts-processed");

      if (chart !== undefined) {
        new Highcharts.Chart(chart.options);
      }
    })
  },
  detach: function(context) {
  }
};

})(jQuery);