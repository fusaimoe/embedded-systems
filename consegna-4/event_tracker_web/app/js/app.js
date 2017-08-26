
function printData(request){
  var tableBody = $('#table-body');
  var url = 'http://192.168.1.72:3000/messages';

  tableBody.empty();

  $.getJSON(url + request, function (data) {
    $.each( data, function( key, val ) {
      var items = "<tr>";
      $.each( this, function( key, val ) {
        items += "<td class='mdl-data-table__cell--non-numeric'>" + val + "</td>";
      });
      items += "</tr>";
      $(tableBody).append( items );
    });
  });
}

$(document).ready(function () {
  printData("");
});

$('.mdl-layout__tab').click(function () {
  $(".mdl-layout__tab").removeClass("is-active");
  $(this).addClass("is-active");
  printData( $(this).data("request") );
});
