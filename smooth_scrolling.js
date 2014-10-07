(function ($) {
  $(document).ready(function(){

    var settings = Drupal.settings.smooth_scrolling;

    $('#first-time').append(settings);
    console.log(settings);
    $.each(settings, function (selector, setting) {
      console.log(selector);
      console.log(setting);


      $('a[href*=#]:not([href=#])').click(function () {
        if (location.pathname.replace(/^\//, '') == this.pathname.replace(/^\//, '') && location.hostname == this.hostname) {
          var target = $(this.hash);
          target = target.length ? target : $('[name=' + this.hash.slice(1) + ']');
          if (target.length) {
            $('html,body').animate({
              scrollTop: target.offset().top
            }, selector);
            return false;
          }
        }
      });
    });

  });

})(jQuery);
