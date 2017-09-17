
function printData(request, id){
  var tableBody = $('#table-body');
  var url = 'http://192.168.1.72:3000/messages';

  tableBody.empty();

  $.getJSON(url + request, function (data) {
    console.log(data);
    $("#table-body").loadTemplate("rowTemplate.html", data,{ success: function(){
      $(".td-id").hide();
      if(id == "temperature"){
        $(".td-presence").hide();
        $(".td-temperature").show();
        $(".td-alarm").hide();
      }else if(id=="presence"){
        $(".td-alarm").hide();
        $(".td-presence").show();
        $(".td-temperature").hide();
      }else {
        $(".td-presence").hide();
        $(".td-alarm").show();
        $(".td-temperature").hide();
      }
    }});

  });

}

$(document).ready(function () {
  printData("?presence=false&alarm=false", "temperature");
});

$('.mdl-layout__tab').click(function () {
  $(".mdl-layout__tab").removeClass("is-active");
  $(this).addClass("is-active");
  printData( $(this).data("request"), $(this).attr("id") );
});
