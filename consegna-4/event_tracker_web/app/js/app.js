
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
  $("td[data-content-text='id']").hide();
  $("td[data-content-text='presence']").hide();
  $("td[data-content-text='alarm']").hide();
});

$('.mdl-layout__tab').click(function () {
  $(".mdl-layout__tab").removeClass("is-active");
  $(this).addClass("is-active");
  printData( $(this).data("request") );

  var id = $(this).attr("id");
  if(id == "temperature"){
    $("td[data-content-text='presence']").hide();
    $("td[data-content-text='alarm']").hide();
  }else if(id=="presence"){
    $("td[data-content-text='temperature']").hide();
    $("td[data-content-text='alarm']").hide();
  }else {
    $("td[data-content-text='temperature']").hide();
    $("td[data-content-text='alarm']").hide();
  }

});
