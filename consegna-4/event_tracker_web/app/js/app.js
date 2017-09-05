
function printData(request){
  var tableBody = $('#table-body');
  var url = 'http://192.168.1.72:3000/messages';

  tableBody.empty();

  $.getJSON(url + request, function (data) {
    console.log(data);
    $("#table-body").loadTemplate("rowTemplate.html", data);
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
