<?php

$files = [
    'sllist_test',
    'dllist_test',
    'cllist_test',
    'stack_test',
];

foreach ($files as $file) {
    echo exec('./' . $file) . PHP_EOL;
}
