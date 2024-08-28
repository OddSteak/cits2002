#!/bin/bash

BIGFILE="/tmp/huge"

if [ ! -f $BIGFILE ]; then
    echo creating $BIGFILE
    for i in {1..1000} ; do cat /bin/bash >> $BIGFILE ; done
fi

echo compiling readfile.c
cc -std=c11 -Wall -Werror -o readfile readfile.c

run() {
    for b in $(seq 200 200 5000) ; do		# 200 400 600 ... 5000
	./readfile $BIGFILE $b
    done
}

# --  nothing needs changing below this line  -----------------------

# some variables to define our output plot:
HTML="plot.html"
TITLE="Comparing buffersize to execution time"


build_html() {
    cat << END_END
<html>
<head>
  <script type='text/javascript' src='https://www.google.com/jsapi'></script>
  <script type='text/javascript'>
    google.load('visualization', '1.1', {packages: ['line']});
    google.setOnLoadCallback(drawChart);

    function drawChart() {
      var options = {
	chart: {
	    lineWidth: 20,
	    title: '$TITLE'
	},
	vAxis: {
	  title: 'milliseconds',
	},
        width:  1000,
        height: 600
      };
      var chart = new google.charts.Line(document.getElementById('linechart_material'));
      var data = new google.visualization.DataTable();

      data.addColumn('number', 'buffersize (bytes)');
      data.addColumn('number', 'milliseconds');

      data.addRows([
END_END

    run | cut -f1,2 | sed -e 's/	/, /' -e 's/.*/	[&],/'

cat << END_END
      ]);
      chart.draw(data, options);
    }
  </script>
</head>

<body>
  <div id='linechart_material' style='margin: 4em;'></div>
</body>
</html>
END_END
}

rm -f $HTML
build_html > $HTML
echo "output is in $HTML"
