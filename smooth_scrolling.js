(function ($) {
  $(document).ready(function(){

    //Get settings from Drupal
    var settings = Drupal.settings.smooth_scrolling;

    $.each(settings, function (selector, setting) {

      //Apply smooth scrolling behaviors
      $('a[href*=#]:not([href=#])').click(function() {
        if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
          var target = $(this.hash);
          target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
          var target_pos = (target.length > 0) ? target.offset().top : 0;
          var fhdr = $(setting);
          var fhdr_height = (fhdr.length > 0) ? fhdr.outerHeight() : 0;
          target_pos -= fhdr_height;
          if (target.length) {
            $('html,body').animate({
              scrollTop: target_pos
            }, parseInt(selector));
            return false;
          }
        }
      });

    });
  });

})(jQuery);
